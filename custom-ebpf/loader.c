#include <bpf/libbpf.h>

int main() {
    struct bpf_object *obj = bpf_object__open_file("openat_trace.o", NULL);
    bpf_object__load(obj);

    bpf_program__attach(obj->programs);  // attach kprobe
    while (1) sleep(1);  // Keep running

    return 0;
}
