#include <stdbool.h>
#include <stdint.h>

#ifndef QUEUE_H
#define QUEUE_H

// Define the node structure
typedef struct Node {
    uint32_t data;
    struct Node* next;
} Node;

// Define the queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function prototypes
Queue* create_queue();
void queue_add(Queue* q, uint32_t value);
uint32_t queue_remove(Queue* q);
bool queue_empty(Queue* q);
void print_queue(Queue* q) ;

#endif // QUEUE_H
