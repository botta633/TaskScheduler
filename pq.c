#include "pq.h"
#include <stdio.h>
// Swap two Task elements
void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}
void init_pq(pq_t *q) {
    q->size = 0;
    pthread_mutex_init(&q->mutex, NULL);
}
// Insert a new task into the priority queue
void insert(pq_t *q, Task task, int (*cmp)(Task, Task)) {
    pthread_mutex_lock(&q->mutex);
    if (q->size == MAX_SIZE) {
    pthread_mutex_unlock(&q->mutex);
        return;
    }
    int index = q->size;
    q->tasks[index] = task;
    q->size++;
    heapify_up(q, index, cmp);
    pthread_mutex_unlock(&q->mutex);
}

// Heapify up (Bubble up)
void heapify_up(pq_t *q, int index, int (*cmp)(Task, Task)) {
    int parent = (index - 1) / 2;
    while (index > 0 && cmp(q->tasks[index], q->tasks[parent]) < 0) {
        swap(&q->tasks[index], &q->tasks[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// Extract the minimum element (bubble-down)
Task extract_min(pq_t *q, int (*cmp)(Task, Task)) {
    pthread_mutex_lock(&q->mutex);
    if (q->size == 0) {
        printf("Heap underflow!\n");
        Task empty = {0}; // Assuming Task has a default empty state
    pthread_mutex_unlock(&q->mutex);
        return empty;
    }

    Task min = q->tasks[0];  // The root (minimum)
    
    // Replace root with the last element
    q->tasks[0] = q->tasks[q->size - 1];
    q->size--;

    // Heapify Down
    heapify_down(q, 0, cmp);

    pthread_mutex_unlock(&q->mutex);
    return min;
}

// Heapify down (Bubble down)
void heapify_down(pq_t *q, int index, int (*cmp)(Task, Task)) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    // Check if left child is smaller
    if (left < q->size && cmp(q->tasks[left], q->tasks[smallest]) < 0) {
        smallest = left;
    }
    // Check if right child is smaller
    if (right < q->size && cmp(q->tasks[right], q->tasks[smallest]) < 0) {
        smallest = right;
    }

    // Swap if necessary and continue
    if (smallest != index) {
        swap(&q->tasks[index], &q->tasks[smallest]);
        heapify_down(q, smallest, cmp);
    }
}
