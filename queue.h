#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100
#include "task.h"
#include <pthread.h>
typedef struct {
    Task *tasks[MAX_SIZE];
    int size;
    pthread_mutex_t mutex;
} sched_queue_t;

// Function prototypes
void init_queue(sched_queue_t *q);
void insert(sched_queue_t *q, Task *task, int (*cmp)(const Task *, const Task *));
Task *extract_min(sched_queue_t *q, int (*cmp)(const Task *, const Task *));
void heapify_up(sched_queue_t *q, int index, int (*cmp)(const Task *, const Task *));
void heapify_down(sched_queue_t *q, int index, int (*cmp)(const Task *, const Task *));
Task *top(sched_queue_t *q);

#endif
