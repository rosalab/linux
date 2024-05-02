// SPDX-License-Identifier: GPL-2.0
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/filter.h>
#include <linux/perf_event.h>
#include <linux/socket.h>
#include <linux/unistd.h>

#include <bpf/bpf_endian.h>
#include <linux/bpf.h>
#include "trace_helpers.h"
#include "testing_helpers.h"

#define _CHECK(condition, tag, duration, format...) ({                  \
        int __ret = !!(condition);                                      \
        int __save_errno = errno;                                       \
        if (__ret) {                                                    \
                test__fail();                                           \
                fprintf(stdout, "%s:FAIL:%s ", __func__, tag);          \
                fprintf(stdout, ##format);                              \
        } else {                                                        \
                fprintf(stdout, "%s:PASS:%s %d nsec\n",                 \
                       __func__, tag, duration);                        \
        }                                                               \
        errno = __save_errno;                                           \
        __ret;                                                          \
})  

int main(void)
{
	const char *file = "test_sk_lookup_kern.bpf.o";
	const char *obj_name = "ref_track";
	DECLARE_LIBBPF_OPTS(bpf_object_open_opts, open_opts,
		.object_name = obj_name,
		.relaxed_maps = true,
	);
	struct bpf_object *obj_iter, *obj = NULL;
	struct bpf_program *prog;
	__u32 duration = 0;
	int err = 0;

	obj_iter = bpf_object__open_file(file, &open_opts);
	if (!ASSERT_OK_PTR(obj_iter, "obj_iter_open_file"))
		return -1;

	if (CHECK(strcmp(bpf_object__name(obj_iter), obj_name), "obj_name",
		  "wrong obj name '%s', expected '%s'\n",
		  bpf_object__name(obj_iter), obj_name))
		goto cleanup;

	bpf_object__for_each_program(prog, obj_iter) {
		struct bpf_program *p;
		const char *name;

		name = bpf_program__name(prog);
		if (!test__start_subtest(name))
			continue;

		obj = bpf_object__open_file(file, &open_opts);
		if (!ASSERT_OK_PTR(obj, "obj_open_file"))
			goto cleanup;

		/* all programs are not loaded by default, so just set
		 * autoload to true for the single prog under test
		 */
		p = bpf_object__find_program_by_name(obj, name);
		bpf_program__set_autoload(p, true);

		/* Expect verifier failure if test name has 'err' */
		if (strncmp(name, "err_", sizeof("err_") - 1) == 0) {
			libbpf_print_fn_t old_print_fn;

			old_print_fn = libbpf_set_print(NULL);
			err = !bpf_object__load(obj);
			libbpf_set_print(old_print_fn);
		} else {
			err = bpf_object__load(obj);
		}
		ASSERT_OK(err, name);

		bpf_object__close(obj);
		obj = NULL;
	}

cleanup:
	bpf_object__close(obj);
	bpf_object__close(obj_iter);
	return 0;
}
