sudo bpftrace -e '
tracepoint:syscalls:sys_enter_openat,
tracepoint:syscalls:sys_enter_close
/pid == 30288/
{
  printf("SYSCALL: %s by %s (PID %d)\n", probe, comm, pid);
}'
