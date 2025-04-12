#include <bpf/libbpf.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct bpf_object *obj;
    struct bpf_program *prog;
    struct bpf_link *link;

    obj = bpf_object__open_file("openat_trace.o", NULL);
    if (!obj) {
        perror("Failed to open BPF object");
        return 1;
    }

    if (bpf_object__load(obj)) {
        perror("Failed to load BPF object");
        return 1;
    }

    prog = bpf_object__find_program_by_name(obj, "bpf_prog");
    if (!prog) {
        fprintf(stderr, "Failed to find BPF program\n");
        return 1;
    }

    link = bpf_program__attach(prog);
    if (!link) {
        fprintf(stderr, "Failed to attach BPF program\n");
        return 1;
    }

    printf("Attached! Press Ctrl+C to quit.\n");
    while (1) sleep(1);
}
