#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Example usage
int main() {
    Queue* q = create_queue();

    queue_add(q, 10);
    queue_add(q, 20);

    printf("Removed: %d\n", queue_remove(q));
    printf("Queue empty: %s\n", queue_empty(q) ? "true" : "false");

    printf("Removed: %d\n", queue_remove(q));
    printf("Queue empty: %s\n", queue_empty(q) ? "true" : "false");

    free(q);
    return 0;
}
