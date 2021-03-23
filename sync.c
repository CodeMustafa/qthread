#include "sync.h"
#include "thread_manage.h"
#include <stdlib.h>

int qmutex_init(qmutext_t *mut) {
  ualarm(0, 0);
  mut->value = 1;
  ualarm(QUANTUM, QUANTUM);
  return 0;
}

int qmutex_lock(qmutext_t *mut) {
  ualarm(0, 0);
  mut->value--;
  ualarm(QUANTUM, QUANTUM);
  while (mut->value < 0);
  return 0;
}

int qmutex_unlock(qmutext_t *mut) {
  ualarm(0, 0);
  mut->value++;
  ualarm(QUANTUM, QUANTUM);
  return 0;
}

int qsem_init(qsem_t *sem, int value) {
  ualarm(0, 0);
  sem->value = value;
  queue_init(&sem->block_queue);
  ualarm(QUANTUM, QUANTUM);
  return 0;
}

int qsem_wait(qsem_t *sem) {
  ualarm(0, 0);
  sem->value--;

  if (sem->value < 0) {
    enqueue(&sem->block_queue, dequeue(&ready_queue));
  }
  ualarm(QUANTUM, QUANTUM);
  return 0;
}

int qsem_signal(qsem_t *sem) {
  ualarm(0, 0);
  sem->value++;
  if (sem->value <= 0) {
    enqueue(&ready_queue, dequeue(&sem->block_queue));
  }
  ualarm(QUANTUM, QUANTUM);
  return 0;
}
