#include <signal.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef UTIL_H
#define UTIL_H

uint32_t test_and_set(uint32_t *flag, uint32_t value);
void park(void);
void unpark(pid_t pid);
void *create_shared_memory(const char *name, size_t size);

#endif // UTIL_H
