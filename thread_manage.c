#include "thread_manage.h"
#include "queue.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void qscheduler(int signal) {
  qthread *curr;
  qthread *next;

  curr = round_robin(&ready_queue);
  next = get_front(&ready_queue);

  curr->state = READY;
  next->state = RUNNING;

  swapcontext(&curr->context, &next->context);
}

static void reaper() {
  qthread *curr;
  qthread *next;

  while (1) {
    ualarm(0, 0);
    curr = dequeue(&ready_queue);
    curr->state = TERMINATED;

    next = get_front(&ready_queue);

    ualarm(QUANTUM, QUANTUM);
    swapcontext(&holder.context, &next->context);
  }
}

int qinit() {
  qthread *main_thread;

  queue_init(&ready_queue);

  main_thread = malloc(sizeof(qthread));
  if (main_thread == NULL)
    return -1;
  main_thread->id = 0;
  main_thread->state = RUNNING;

  enqueue(&ready_queue, main_thread);

  void *stack_mem;

  if (getcontext(&holder.context) == -1)
    return -1;

  stack_mem = malloc(DEF_STACK_SZ);
  if (stack_mem == NULL)
    return -1;
  holder.state = READY;
  holder.context.uc_stack.ss_sp = stack_mem;
  holder.context.uc_stack.ss_size = DEF_STACK_SZ;
  holder.context.uc_link = NULL;
  makecontext(&holder.context, reaper, 0);

  struct sigaction act, oact;

  act.sa_handler = qscheduler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  sigaction(SIGALRM, &act, &oact);
  ualarm(QUANTUM, QUANTUM);

  return 0;
}

int qcreate(qthread *thread, void (*func)(), void *arg) {

  void *stack_mem;

  if (getcontext(&thread->context) == -1)
    return -1;

  stack_mem = malloc(DEF_STACK_SZ);
  if (stack_mem == NULL)
    return -1;
  thread->id = ++thread_counter;
  thread->state = READY;
  thread->context.uc_stack.ss_sp = stack_mem;
  thread->context.uc_stack.ss_size = DEF_STACK_SZ;
  thread->context.uc_link = &holder.context;
  makecontext(&thread->context, func, 1, arg);

  if (enqueue(&ready_queue, thread) == -1) {
    free(stack_mem);
    return -1;
  }

  return 0;
}

void qyield() {
  qthread *curr;
  qthread *next;

  ualarm(0, 0);
  curr = round_robin(&ready_queue);
  next = get_front(&ready_queue);

  curr->state = READY;
  next->state = RUNNING;

  ualarm(QUANTUM, QUANTUM);
  swapcontext(&curr->context, &next->context);
}

int qjoin(qthread *t) {
  while (t->state != TERMINATED)
    qyield(t);
  return 0;
}

int qget_id() {
  qthread *curr;
  curr = get_front(&ready_queue);
  return (curr->id);
}
