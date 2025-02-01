#ifndef POOL_H
#define POOL_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdatomic.h>


typedef struct Node {
    struct Node *next;
    int data;
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
void add_task(int);




#endif 


