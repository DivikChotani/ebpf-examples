# eBPF Project Overview

This project demonstrates how eBPF (Extended Berkeley Packet Filter) can be used to trace system calls in the Linux kernel. It focuses on monitoring the `openat` syscall by attaching a BPF program to a kernel probe (kprobe).

## Project Structure

Key files in the project:

- **Makefile** - Automates the build process
- **loader** - Compiled userspace program (created from loader.c)
- **loader.c** - C program that loads and attaches the eBPF program
- **openat_trace.c** - The eBPF program that runs in kernel space
- **vmlinux.h** - BTF type definitions from the kernel

## openat_trace.c - The BPF Program

This is the kernel-space eBPF program that gets executed every time the specified syscall (`openat`) is invoked.

Key components:
- `SEC("kprobe/sys_openat")`: Annotation that tells the kernel to run this code whenever `sys_openat` is called
- `bpf_prog`: The actual function that gets called in the kernel
- `bpf_printk`: Function similar to `printf` but logs to the kernel trace buffer
- `LICENSE`: Required for compliance with kernel requirements

## loader.c - Userspace Loader Program

This C program uses the libbpf library to:

1. Load the compiled `openat_trace.o` object file
2. Attach it to the kprobe
3. Keep the program running so the eBPF program stays attached

## vmlinux.h - Kernel Type Definitions

This header file is generated from the kernel's BTF (BPF Type Format) metadata using:

```bash
bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
```

It provides access to definitions for kernel types, structs, functions, etc., allowing the eBPF program to interact with real kernel memory layouts. This is critical for BPF programs that need to access kernel data structures.

## What This eBPF Setup Does

eBPF allows you to safely inject programs into the kernel to observe or even modify system behavior without writing kernel modules.

This project specifically uses:
- **kprobes**: To hook into kernel function calls (specifically `openat`)
- **bpf_printk**: To log trace output to the kernel's trace buffer
- **libbpf**: In userspace to interact with BPF syscalls

The result is a system that monitors when files are opened through the `openat` syscall, providing visibility into file operations without modifying the kernel code.