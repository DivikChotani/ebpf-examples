#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("kprobe/__arm64_sys_openat")
int bpf_prog(void *ctx) {
    bpf_printk("openat() called!\n");
    return 0;
}

char LICENSE[] SEC("license") = "GPL";
