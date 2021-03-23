			        ////////////////////////////////
			       //	 Quark(qthread)  Library // 
			      //    Mustafa Abdelwahab      //
			 	 ////////////////////////////////
#ifndef qh
#define qh

#include<ucontext.h>
#include"queue.h"
#include"sync.h"

/*
#define RUNNING		1
#define READY		2
#define TERMINATED	3*/
#define QUANTUM	1500//150000
#define DEF_STACK_SZ	16384

typedef enum State{
	RUNNING,READY,TERMINATED
}s;

typedef struct _tag_qthread
{
 unsigned short id;
 enum State state;
 ucontext_t context; 
}qthread;

static queue_t ready_queue;
static qthread holder;
static unsigned short thread_counter = 0;


int qinit();
int qcreate(qthread *,void(*)(),void*);
int qjoin(qthread *);
void qyield();
int qget_id();
#endif
