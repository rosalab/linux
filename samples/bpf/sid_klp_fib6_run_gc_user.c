#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>


int main(int argc, char **argv){

    struct bpf_link *link1 = NULL;
    struct bpf_link *link2 = NULL;
    struct bpf_link *link3 = NULL;

    struct bpf_program *prog1;
    struct bpf_program *prog2;
    struct bpf_program *prog3;

    struct bpf_object *obj;

    char filename[256];
    snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

    obj = bpf_object__open_file(filename, NULL);
    if(libbpf_get_error(obj)){
        fprintf(stderr, "Error: opening BPF obj file");
        return 0;
    }

    prog1 = bpf_object__find_program_by_name(obj, "fentry_func");
    if(!prog1){
        fprintf(stderr,"fentry_func: finding the prog in the object file failed\n");
        goto cleanup;
    }
    prog2 = bpf_object__find_program_by_name(obj, "fmod_ret_func");
    if(!prog2){
        fprintf(stderr,"fmod_ret_func: finding the prog in the object file failed\n");
        goto cleanup;
    }
    prog3 = bpf_object__find_program_by_name(obj, "fexit_func");
    if(!prog3){
        fprintf(stderr,"fexit_func: finding the prog in the object file failed\n");
        goto cleanup;
    }

    printf("Before Loading\n");
    if (bpf_object__load(obj)) {
                fprintf(stderr, "ERROR: loading BPF object file failed\n");
                goto cleanup;
    }

    printf("Before Attaching\n");
    link1 = bpf_program__attach(prog1);
    if(libbpf_get_error(link1)){
        fprintf(stderr, "ERROR-fentry_func: bpf_program__attach failed : %ld\n", libbpf_get_error(link1));
        link1 = NULL;
        goto cleanup;
    }else{
        fprintf(stderr, "fentry_func: Attachment is done\n");
    }
    link2 = bpf_program__attach(prog2);
    if(libbpf_get_error(link2)){
        fprintf(stderr, "ERROR-fmod_ret_func: bpf_program__attach failed : %ld\n", libbpf_get_error(link2));
        link2 = NULL;
        goto cleanup;
    }else{
        fprintf(stderr, "fmod_ret_func: Attachment is done\n");
    }
    link3 = bpf_program__attach(prog3);
    if(libbpf_get_error(link3)){
        fprintf(stderr, "ERROR-fexit_func: bpf_program__attach failed : %ld\n", libbpf_get_error(link3));
        link3 = NULL;
        goto cleanup;
    }else{
        fprintf(stderr, "fexit_func: Attachment is done\n");
    }

    while(1){
	// nothing
    }
    cleanup:
            bpf_link__destroy(link1);
            bpf_link__destroy(link2);
            bpf_link__destroy(link3);
            bpf_object__close(obj);
            return 0;

}
