#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../include/util.h"

#define WAKEUP_SIGNAL SIGUSR1

uint32_t test_and_set(uint32_t *flag, uint32_t value) {
    return __sync_lock_test_and_set(flag, value);
}

void park() {
    sigset_t mask;
    int32_t sig;

    sigemptyset(&mask);
    sigaddset(&mask, WAKEUP_SIGNAL);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    printf("Process %d is waiting for WAKEUP_SIGNAL...\n", getpid());

    sigwait(&mask, &sig);

    printf("Process %d received WAKEUP_SIGNAL!\n", getpid());
}

void unpark(pid_t pid) {
    printf("Sending WAKEUP_SIGNAL to process %d...\n", pid);
    kill(pid, WAKEUP_SIGNAL);
    printf("Sending WAKEUP_SIGNAL to process %d...\n", pid);
}

void *create_shared_memory(const char *name, size_t size) {
  uint32_t shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == (uint32_t)-1) {
    fprintf(stderr, "Error: shm_open failed");
    exit(EXIT_FAILURE);
  }
  if (ftruncate(shm_fd, size) == -1) {
    fprintf(stderr, "Error: ftruncate failed");
    exit(EXIT_FAILURE);
  }
  void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (addr == MAP_FAILED) {
    fprintf(stderr, "Error: mmap failed");
    exit(EXIT_FAILURE);
  }
  return addr;
}
