#ifndef POOL_H
#define POOL_H
#include "../schedulers.h"
#include "../task.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  Task *task;
  struct scheduler *scheduler;
} runnable;

typedef struct Node {
  struct Node *next;
  runnable *runnable;
} node_t;

typedef struct queue {
  node_t *head;
  node_t *tail;
  pthread_mutex_t head_mutex;
  pthread_mutex_t tail_mutex;
  atomic_int size;
  pthread_cond_t empty_var;
  pthread_cond_t full_var;
} queue_t;

typedef struct thread_pool {
  pthread_t threads[10];
  queue_t queue;
} pool_t;

void init_pool();
void add_runnable(runnable *);

#endif
