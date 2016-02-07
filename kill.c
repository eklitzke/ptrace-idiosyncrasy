#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

#include "./parse_pid.h"

int main(int argc, char **argv) {
  pid_t pid;
  if ((pid = parse_pid(argc, argv)) <= 0) {
    return 1;
  } else if (kill(pid, SIGSTOP)) {
    perror("kill()");
  } else {
    printf("kill successful\n");
  }
  return 0;
}
