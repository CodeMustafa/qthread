#ifndef queue_h
#define queue_h

typedef struct _tag_linklist_t {
  void *elm;
  struct _tag_linklist_t *next;
} linklist_t;

typedef struct _tag_queue_t {
  linklist_t *head;
  linklist_t *tail;
  int queue_length;
} queue_t;

void queue_init(queue_t *);
int enqueue(queue_t *, void *);
void *dequeue(queue_t *);
int is_queue_empty(queue_t *);
void *round_robin(queue_t *);
void *get_front(queue_t *);
int get_length(queue_t *);
#endif
