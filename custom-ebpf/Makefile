CLANG=clang
CFLAGS=-O2 -g -Wall -target bpf \
  -I/usr/include \
  -I/usr/src/linux-headers-$(shell uname -r)/include

all:
	$(CLANG) $(CFLAGS) -c openat_trace.c -o openat_trace.o
