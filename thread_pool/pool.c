#include "pool.h"
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
static pool_t pool;

#define MAX_QUEUE_SIZE 30

static int dequeue() {
    int val = pool.queue.head->data;
    struct Node *temp = pool.queue.head;
    pool.queue.head = temp->next;
    printf("%d\n", val);
    atomic_fetch_sub_explicit(&pool.queue.size, 1, memory_order_relaxed);
    free(temp);

    return val;
}

static void enqueue(int val) {
    node_t *new_node = malloc(sizeof(node_t));
    pool.queue.tail->data = val;
    pool.queue.tail->next = new_node;
    pool.queue.tail = new_node;
    atomic_fetch_add_explicit(&pool.queue.size, 1, memory_order_relaxed);
}

void add_task(int val) {
    pthread_mutex_lock(&pool.queue.tail_mutex);
    while(atomic_load_explicit(&pool.queue.size, memory_order_relaxed) == MAX_QUEUE_SIZE)
        pthread_cond_wait(&pool.queue.full_var, &pool.queue.tail_mutex);
    enqueue(val);
    pthread_cond_signal(&pool.queue.empty_var);
    pthread_mutex_unlock(&pool.queue.tail_mutex);

}
static void *consume(void *args) {
    pthread_mutex_lock(&pool.queue.head_mutex);
    while(atomic_load_explicit(&pool.queue.size, memory_order_relaxed) == 0)
        pthread_cond_wait(&pool.queue.empty_var, &pool.queue.head_mutex);
   dequeue();
   pthread_cond_signal(&pool.queue.full_var);
   pthread_mutex_unlock(&pool.queue.head_mutex);

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
    for(int i = 0; i < 10; i++)
        pthread_create(&pool.threads[i], NULL, consume, NULL);
} 

