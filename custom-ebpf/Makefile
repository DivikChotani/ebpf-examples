CLANG ?= clang
CFLAGS = -g -O2 -target bpf -D__TARGET_ARCH_x86 -I. 

all: openat_trace.o

openat_trace.o: openat_trace.c vmlinux.h
	$(CLANG) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
