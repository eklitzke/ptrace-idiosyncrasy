#include <poll.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork()");
    return 1;
  }
  if (pid != 0) {
    printf("%d\n", pid);
    poll(NULL, 0, -1);
  }
  return 0;
}
