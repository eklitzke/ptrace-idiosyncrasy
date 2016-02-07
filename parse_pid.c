#include "./parse_pid.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

pid_t parse_pid(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: %s <pid>\n", argv[0]);
    return -1;
  }
  long pid = strtol(argv[1], NULL, 10);
  if ((errno == ERANGE && (pid == LONG_MAX || pid == LONG_MIN)) ||
      (errno == EINVAL && pid == 0)) {
    perror("strtol");
    return -1;
  }
  if (pid < 0) {
    printf("cowardly refusing to kill negative pid %d\n", pid);
    return -1;
  }
  return pid;
}
