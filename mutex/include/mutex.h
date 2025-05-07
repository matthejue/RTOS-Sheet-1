#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include <sys/types.h>

typedef struct __lock_t {
    uint32_t flag;
    struct Queue *q;
} lock_t;

// Mutex API
void lock_init(lock_t *m);
void lock(lock_t *m);
void unlock(lock_t *m);

#endif // MUTEX_H
