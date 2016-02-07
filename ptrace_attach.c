#include <stdio.h>
#include <sys/ptrace.h>

#include "./parse_pid.h"

int main(int argc, char **argv) {
  pid_t pid;
  if ((pid = parse_pid(argc, argv)) <= 0) {
    return 1;
  } else if (ptrace(PTRACE_ATTACH, pid, NULL, NULL)) {
    perror("PTRACE_ATTACH");
    return 1;
  } else {
    printf("PTRACE_ATTACH successful\n");
  }
  return 0;
}
