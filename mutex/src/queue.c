#include "../include/util.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>

typedef struct Node {
  uint32_t data;
  struct Node *next;
  char shm_name[64];
} Node;

typedef struct Queue {
  Node *front;
  Node *rear;
} Queue;

Queue *create_queue() {
  Queue *q = (Queue *)create_shared_memory("/queue_shm", sizeof(Queue));

  q->front = q->rear = NULL;
  return q;
}

void queue_add(Queue *q, int value) {
  char shm_name[64];
  snprintf(shm_name, sizeof(shm_name), "/node_shm_%ld", time(NULL));
  Node *new_node = (Node *)create_shared_memory(shm_name, sizeof(Node));
  strncpy(new_node->shm_name, shm_name, sizeof(new_node->shm_name) - 1);
  new_node->shm_name[sizeof(new_node->shm_name) - 1] = '\0';

  new_node->data = value;
  new_node->next = NULL;

  if (q->rear == NULL) {
    q->front = q->rear = new_node;
    return;
  }

  q->rear->next = new_node;
  q->rear = new_node;
}

int queue_remove(Queue *q) {
  if (q->front == NULL) {
    printf("Queue is empty.\n");
    return -1;
  }

  Node *temp = q->front;
  int value = temp->data;

  q->front = q->front->next;

  if (q->front == NULL) {
    q->rear = NULL;
  }

  shm_unlink(temp->shm_name);
  return value;
}

void print_queue(Queue *q) {
  if (q->front == NULL) {
    printf("Queue is empty.\n");
    return;
  }

  Node *current = q->front;
  printf("Queue state: ");
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

bool queue_empty(Queue *q) { return q->front == NULL; }
