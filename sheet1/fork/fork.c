#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid_child;
  pid_child = fork();
  if (pid_child == 0) {
    printf("Child: My PID is %d\n", getpid());
    exit(EXIT_SUCCESS);
  } else if (pid_child > 0) {
    printf("Parent: My PID is %d\n", getpid());
    printf("Parent: The PID of my child is %d\n", pid_child);
    exit(EXIT_SUCCESS);
  } else {
    fprintf(stderr, "Error: Fork failed");
    exit(EXIT_FAILURE);
  }
}
