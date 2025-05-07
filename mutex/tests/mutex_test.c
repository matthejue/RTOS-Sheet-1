#define _POSIX_C_SOURCE 200809L

#include "../include/mutex.h"
#include "../include/util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define NUM_PROCESSES 2
#define NUM_ITERATIONS 100000000

lock_t *mutex;
uint32_t *shared_counter;

void critical_section() {
  lock(mutex);
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // if (*shared_counter % 100000 == 0) {
    //   printf("Value of shared_counter: %u of process %u\n", *shared_counter,
    //          getpid());
    // }
    (*shared_counter)++;
  }
  printf("Finished!\n");
  unlock(mutex);
}

int main() {
  mutex = (lock_t *)create_shared_memory("/mutex_shm", sizeof(lock_t));
  shared_counter =
      (uint32_t *)create_shared_memory("/counter_shm", sizeof(uint32_t));

  lock_init(mutex);
  *shared_counter = 0;

  pid_t pids[NUM_PROCESSES];
  for (int i = 0; i < NUM_PROCESSES; i++) {
    if ((pids[i] = fork()) == 0) {
      // Child process
      critical_section();
      exit(EXIT_SUCCESS);
    }
  }

  // Parent process waits for all children to finish
  for (int i = 0; i < NUM_PROCESSES; i++) {
    waitpid(pids[i], NULL, 0);
  }

  printf("Final value of shared_counter: %u\n", *shared_counter);

  shm_unlink("/mutex_shm");
  shm_unlink("/counter_shm");

  return 0;
}
