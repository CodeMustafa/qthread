////////////////////////////////
//	 Quark(qthread)  Library //
//    Mustafa Abdelwahab      //
////////////////////////////////
#ifndef sync_h
#define sync_h

#include "queue.h"

typedef struct _tag_qmutext_t {
  int value;
} qmutext_t;

typedef struct _tag_qsem_t {
  int value;
  queue_t block_queue;
} qsem_t;

int qmutex_init(qmutext_t *);

int qmutex_lock(qmutext_t *);

int qmutex_unlock(qmutext_t *);

int qsem_init(qsem_t *, int);

int qsem_wait(qsem_t *);

int qsem_signal(qsem_t *);

#endif
