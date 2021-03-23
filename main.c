#include "quark.h"
#include <stdio.h>

int x = 0;

qmutext_t mut;
qsem_t sem;

void f1() {
  int j, i = 0;
  for (j = 0; j < 100; j++)
    for (i = 0; i < 1000; i++) {
      qmutex_lock(&mut);
      x = x + 1;
      qmutex_unlock(&mut);
    }
  printf("thread %d is Finished!\n", qget_id());
}

void f2() {
  int j, i = 0;
  for (j = 0; j < 100; j++)
    for (i = 0; i < 1000; i++) {
      qmutex_lock(&mut);
      x = x - 1;
      qmutex_unlock(&mut);
    }
  printf("thread %d is Finished!\n", qget_id());
}

int main(int argc, char **argv) {
  int MAX_TH_NO = 4;

  if (argc > 1)
    MAX_TH_NO = atoi(argv[1]);

  qinit(); // initlize the program
  qmutex_init(&mut);
  qthread T[MAX_TH_NO]; // = malloc(MAX_TH_NO*sizeof(qthread));

  int i = 0;

  for (i; i < MAX_TH_NO; i++) {
    if (i % 2 == 0)
      qcreate(&T[i], f1, NULL); // create threads
    else
      qcreate(&T[i], f2, NULL); // create threads
  }

  for (i = 0; i < MAX_TH_NO; i++)
    qjoin(&T[i]);

  printf("back to main : %d\n", x);
  return 0;
}
