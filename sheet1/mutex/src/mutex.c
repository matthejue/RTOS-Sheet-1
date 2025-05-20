#include "../include/queue.h"
#include "../include/util.h"
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

typedef struct __lock_t {
  uint32_t flag;
  Queue *q;
} lock_t;

void lock_init(lock_t *m) {
  m->flag = 0;
  m->q = create_queue();
}

void lock(lock_t *m) {
  printf("Process %d is trying to acquire the lock...\n", getpid());
  if (test_and_set(&m->flag, 1)) {
    queue_add(m->q, getpid());
    print_queue(m->q);
    park();
  }
  printf("Process %d acquired the lock!\n", getpid());
}

void unlock(lock_t *m) {
  printf("Process %d is releasing the lock...\n", getpid());
  print_queue(m->q);
  if (queue_empty(m->q)) {
    m->flag = 0;
  } else {
    unpark(queue_remove(m->q));
  }
  printf("Process %d released the lock!\n", getpid());
  fflush(stdout);
}
