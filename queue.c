#include "queue.h"
#include <stdlib.h>

void queue_init(queue_t *q) {
  q->head = q->tail = NULL;
  q->queue_length = 0;
}

int enqueue(queue_t *q, void *elm) {

  linklist_t *node;
  node = malloc(sizeof(linklist_t));

  if (node == NULL)
    return -1;

  node->elm = elm;
  node->next = NULL;

  if (q->tail == NULL) {
    q->head = q->tail = node;
  } else {
    q->tail->next = node;
    q->tail = node;

    // q->tail->next = NULL;
  }

  q->queue_length++;
  return 0;
}

void *dequeue(queue_t *q) {
  linklist_t *node;
  void *elm;
  if (q->head == NULL)
    return NULL;

  node = q->head;
  q->head = q->head->next;
  elm = node->elm;
  node->next = NULL;

  free(node);
  q->queue_length--;
  return elm;
}

int is_queue_empty(queue_t *q) { return (q->head == NULL); }

void *round_robin(queue_t *q) {
  if (q->head == NULL)
    return NULL;
  if (q->head == q->tail)
    return q->head->elm;

  q->tail->next = q->head;
  q->head = q->head->next;
  q->tail = q->tail->next;
  q->tail->next = NULL;

  return q->tail->elm;
}

void *get_front(queue_t *q) { return (q->head->elm); }

int get_length(queue_t *q) { return q->queue_length; }
