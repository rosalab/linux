// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021 IBM Corporation
 */

#include <linux/module.h>
#include <crypto/internal/ecc.h>
#include <crypto/internal/sig.h>
#include <crypto/ecdh.h>
#include <crypto/sha2.h>
#include <crypto/sig.h>

struct ecc_ctx {
	unsigned int curve_id;
	const struct ecc_curve *curve;

	bool pub_key_set;
	u64 x[ECC_MAX_DIGITS]; /* pub key x and y coordinates */
	u64 y[ECC_MAX_DIGITS];
	struct ecc_point pub_key;
};

static int _ecdsa_verify(struct ecc_ctx *ctx, const u64 *hash, const u64 *r, const u64 *s)
{
	const struct ecc_curve *curve = ctx->curve;
	unsigned int ndigits = curve->g.ndigits;
	u64 s1[ECC_MAX_DIGITS];
	u64 u1[ECC_MAX_DIGITS];
	u64 u2[ECC_MAX_DIGITS];
	u64 x1[ECC_MAX_DIGITS];
	u64 y1[ECC_MAX_DIGITS];
	struct ecc_point res = ECC_POINT_INIT(x1, y1, ndigits);

	/* 0 < r < n  and 0 < s < n */
	if (vli_is_zero(r, ndigits) || vli_cmp(r, curve->n, ndigits) >= 0 ||
	    vli_is_zero(s, ndigits) || vli_cmp(s, curve->n, ndigits) >= 0)
		return -EBADMSG;

	/* hash is given */
	pr_devel("hash : %016llx %016llx ... %016llx\n",
		 hash[ndigits - 1], hash[ndigits - 2], hash[0]);

	/* s1 = (s^-1) mod n */
	vli_mod_inv(s1, s, curve->n, ndigits);
	/* u1 = (hash * s1) mod n */
	vli_mod_mult_slow(u1, hash, s1, curve->n, ndigits);
	/* u2 = (r * s1) mod n */
	vli_mod_mult_slow(u2, r, s1, curve->n, ndigits);
	/* res = u1*G + u2 * pub_key */
	ecc_point_mult_shamir(&res, u1, &curve->g, u2, &ctx->pub_key, curve);

	/* res.x = res.x mod n (if res.x > order) */
	if (unlikely(vli_cmp(res.x, curve->n, ndigits) == 1))
		/* faster alternative for NIST p521, p384, p256 & p192 */
		vli_sub(res.x, res.x, curve->n, ndigits);

	if (!vli_cmp(res.x, r, ndigits))
		return 0;

	return -EKEYREJECTED;
}

/*
 * Verify an ECDSA signature.
 */
static int ecdsa_verify(struct crypto_sig *tfm,
			const void *src, unsigned int slen,
			const void *digest, unsigned int dlen)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);
	size_t bufsize = ctx->curve->g.ndigits * sizeof(u64);
	const struct ecdsa_raw_sig *sig = src;
	u64 hash[ECC_MAX_DIGITS];

	if (unlikely(!ctx->pub_key_set))
		return -EINVAL;

	if (slen != sizeof(*sig))
		return -EINVAL;

	if (bufsize > dlen)
		bufsize = dlen;

	ecc_digits_from_bytes(digest, bufsize, hash, ctx->curve->g.ndigits);

	return _ecdsa_verify(ctx, hash, sig->r, sig->s);
}

static int ecdsa_ecc_ctx_init(struct ecc_ctx *ctx, unsigned int curve_id)
{
	ctx->curve_id = curve_id;
	ctx->curve = ecc_get_curve(curve_id);
	if (!ctx->curve)
		return -EINVAL;

	return 0;
}


static void ecdsa_ecc_ctx_deinit(struct ecc_ctx *ctx)
{
	ctx->pub_key_set = false;
}

static int ecdsa_ecc_ctx_reset(struct ecc_ctx *ctx)
{
	unsigned int curve_id = ctx->curve_id;
	int ret;

	ecdsa_ecc_ctx_deinit(ctx);
	ret = ecdsa_ecc_ctx_init(ctx, curve_id);
	if (ret == 0)
		ctx->pub_key = ECC_POINT_INIT(ctx->x, ctx->y,
					      ctx->curve->g.ndigits);
	return ret;
}

/*
 * Set the public ECC key as defined by RFC5480 section 2.2 "Subject Public
 * Key". Only the uncompressed format is supported.
 */
static int ecdsa_set_pub_key(struct crypto_sig *tfm, const void *key,
			     unsigned int keylen)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);
	unsigned int digitlen, ndigits;
	const unsigned char *d = key;
	int ret;

	ret = ecdsa_ecc_ctx_reset(ctx);
	if (ret < 0)
		return ret;

	if (keylen < 1 || ((keylen - 1) & 1) != 0)
		return -EINVAL;
	/* we only accept uncompressed format indicated by '4' */
	if (d[0] != 4)
		return -EINVAL;

	keylen--;
	digitlen = keylen >> 1;

	ndigits = DIV_ROUND_UP(digitlen, sizeof(u64));
	if (ndigits != ctx->curve->g.ndigits)
		return -EINVAL;

	d++;

	ecc_digits_from_bytes(d, digitlen, ctx->pub_key.x, ndigits);
	ecc_digits_from_bytes(&d[digitlen], digitlen, ctx->pub_key.y, ndigits);

	ret = ecc_is_pubkey_valid_full(ctx->curve, &ctx->pub_key);

	ctx->pub_key_set = ret == 0;

	return ret;
}

static void ecdsa_exit_tfm(struct crypto_sig *tfm)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);

	ecdsa_ecc_ctx_deinit(ctx);
}

static unsigned int ecdsa_key_size(struct crypto_sig *tfm)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);

	return ctx->curve->nbits;
}

static unsigned int ecdsa_digest_size(struct crypto_sig *tfm)
{
	/*
	 * ECDSA key sizes are much smaller than RSA, and thus could
	 * operate on (hashed) inputs that are larger than the key size.
	 * E.g. SHA384-hashed input used with secp256r1 based keys.
	 * Return the largest supported hash size (SHA512).
	 */
	return SHA512_DIGEST_SIZE;
}

static int ecdsa_nist_p521_init_tfm(struct crypto_sig *tfm)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);

	return ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P521);
}

static struct sig_alg ecdsa_nist_p521 = {
	.verify = ecdsa_verify,
	.set_pub_key = ecdsa_set_pub_key,
	.key_size = ecdsa_key_size,
	.digest_size = ecdsa_digest_size,
	.init = ecdsa_nist_p521_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cra_name = "ecdsa-nist-p521",
		.cra_driver_name = "ecdsa-nist-p521-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = sizeof(struct ecc_ctx),
	},
};

static int ecdsa_nist_p384_init_tfm(struct crypto_sig *tfm)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);

	return ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P384);
}

static struct sig_alg ecdsa_nist_p384 = {
	.verify = ecdsa_verify,
	.set_pub_key = ecdsa_set_pub_key,
	.key_size = ecdsa_key_size,
	.digest_size = ecdsa_digest_size,
	.init = ecdsa_nist_p384_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cra_name = "ecdsa-nist-p384",
		.cra_driver_name = "ecdsa-nist-p384-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = sizeof(struct ecc_ctx),
	},
};

static int ecdsa_nist_p256_init_tfm(struct crypto_sig *tfm)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);

	return ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P256);
}

static struct sig_alg ecdsa_nist_p256 = {
	.verify = ecdsa_verify,
	.set_pub_key = ecdsa_set_pub_key,
	.key_size = ecdsa_key_size,
	.digest_size = ecdsa_digest_size,
	.init = ecdsa_nist_p256_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cra_name = "ecdsa-nist-p256",
		.cra_driver_name = "ecdsa-nist-p256-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = sizeof(struct ecc_ctx),
	},
};

static int ecdsa_nist_p192_init_tfm(struct crypto_sig *tfm)
{
	struct ecc_ctx *ctx = crypto_sig_ctx(tfm);

	return ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P192);
}

static struct sig_alg ecdsa_nist_p192 = {
	.verify = ecdsa_verify,
	.set_pub_key = ecdsa_set_pub_key,
	.key_size = ecdsa_key_size,
	.digest_size = ecdsa_digest_size,
	.init = ecdsa_nist_p192_init_tfm,
	.exit = ecdsa_exit_tfm,
	.base = {
		.cra_name = "ecdsa-nist-p192",
		.cra_driver_name = "ecdsa-nist-p192-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = sizeof(struct ecc_ctx),
	},
};
static bool ecdsa_nist_p192_registered;

static int __init ecdsa_init(void)
{
	int ret;

	/* NIST p192 may not be available in FIPS mode */
	ret = crypto_register_sig(&ecdsa_nist_p192);
	ecdsa_nist_p192_registered = ret == 0;

	ret = crypto_register_sig(&ecdsa_nist_p256);
	if (ret)
		goto nist_p256_error;

	ret = crypto_register_sig(&ecdsa_nist_p384);
	if (ret)
		goto nist_p384_error;

	ret = crypto_register_sig(&ecdsa_nist_p521);
	if (ret)
		goto nist_p521_error;

	ret = crypto_register_template(&ecdsa_x962_tmpl);
	if (ret)
		goto x962_tmpl_error;

	ret = crypto_register_template(&ecdsa_p1363_tmpl);
	if (ret)
		goto p1363_tmpl_error;

	return 0;

p1363_tmpl_error:
	crypto_unregister_template(&ecdsa_x962_tmpl);

x962_tmpl_error:
	crypto_unregister_sig(&ecdsa_nist_p521);

nist_p521_error:
	crypto_unregister_sig(&ecdsa_nist_p384);

nist_p384_error:
	crypto_unregister_sig(&ecdsa_nist_p256);

nist_p256_error:
	if (ecdsa_nist_p192_registered)
		crypto_unregister_sig(&ecdsa_nist_p192);
	return ret;
}

static void __exit ecdsa_exit(void)
{
	crypto_unregister_template(&ecdsa_x962_tmpl);
	crypto_unregister_template(&ecdsa_p1363_tmpl);

	if (ecdsa_nist_p192_registered)
		crypto_unregister_sig(&ecdsa_nist_p192);
	crypto_unregister_sig(&ecdsa_nist_p256);
	crypto_unregister_sig(&ecdsa_nist_p384);
	crypto_unregister_sig(&ecdsa_nist_p521);
}

module_init(ecdsa_init);
module_exit(ecdsa_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefan Berger <stefanb@linux.ibm.com>");
MODULE_DESCRIPTION("ECDSA generic algorithm");
MODULE_ALIAS_CRYPTO("ecdsa-nist-p192");
MODULE_ALIAS_CRYPTO("ecdsa-nist-p256");
MODULE_ALIAS_CRYPTO("ecdsa-nist-p384");
MODULE_ALIAS_CRYPTO("ecdsa-nist-p521");
MODULE_ALIAS_CRYPTO("ecdsa-generic");
