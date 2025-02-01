#include "pool.h"
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
static pool_t pool;

#define MAX_QUEUE_SIZE 5

static runnable *dequeue() {
    runnable *runnable = pool.queue.head->runnable;
    struct Node *temp = pool.queue.head;
    pool.queue.head = temp->next;
    atomic_fetch_sub_explicit(&pool.queue.size, 1, memory_order_relaxed);
    free(temp);
    return runnable;
}

static void enqueue(runnable *runnable) {
    node_t *new_node = malloc(sizeof(node_t));
    pool.queue.tail->runnable = runnable;
    pool.queue.tail->next = new_node;
    pool.queue.tail = new_node;
    atomic_fetch_add_explicit(&pool.queue.size, 1, memory_order_relaxed);
}

void add_runnable(runnable *runnable) {
    pthread_mutex_lock(&pool.queue.tail_mutex);
    while(atomic_load_explicit(&pool.queue.size, memory_order_relaxed) == MAX_QUEUE_SIZE)
        pthread_cond_wait(&pool.queue.full_var, &pool.queue.tail_mutex);
    enqueue(runnable);
    pthread_cond_signal(&pool.queue.empty_var);
    pthread_mutex_unlock(&pool.queue.tail_mutex);
}

static void *consume(void *args) {
    pthread_mutex_lock(&pool.queue.head_mutex);
    while(atomic_load_explicit(&pool.queue.size, memory_order_relaxed) == 0)
        pthread_cond_wait(&pool.queue.empty_var, &pool.queue.head_mutex);
   runnable *runnable = dequeue();
   pthread_cond_signal(&pool.queue.full_var);
   pthread_mutex_unlock(&pool.queue.head_mutex);
   runnable->scheduler->schedule(runnable->task);
   return NULL;
}

static void init_queue(queue_t *queue) {
    queue->head = queue->tail = malloc(sizeof(node_t));
    atomic_store(&queue->size, 0);
    pthread_mutex_init(&queue->head_mutex, NULL);
    pthread_mutex_init(&queue->tail_mutex, NULL);
    pthread_cond_init(&queue->empty_var, NULL);
    pthread_cond_init(&queue->full_var, NULL);;
}

void init_pool() {
    init_queue(&pool.queue);
    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
        pthread_create(&pool.threads[i], NULL, consume, NULL);
} 

