#ifndef pq
#define pq

#define MAX_SIZE 100
#include "task.h"
#include <pthread.h>
typedef struct {
    Task *tasks[MAX_SIZE];
    int size;
    pthread_mutex_t mutex;
} pq_t;

// Function prototypes
void init_pq(pq_t *q);
void insert(pq_t *q, Task *task, int (*cmp)(const Task *, const Task *));
Task *extract_min(pq_t *q, int (*cmp)(Task, Task));
void heapify_up(pq_t *q, int index, int (*cmp)(Task, Task));
void heapify_down(pq_t *q, int index, int (*cmp)(Task, Task));


#endif
