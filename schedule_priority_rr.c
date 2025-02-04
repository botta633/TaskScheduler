//
//  schedule_priority.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 23/01/2021.
//

#include "custom-sched.h"
#include "queue.h"
#include "task.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

static scheduler *priority_rr;
Task *current_task = NULL;

// comparing tasks based on their priority
int cmpfunc(const Task *a, const Task *b) {

  return b->priority - a->priority;
}

void schedule_priority_rr(Task *task) {
    insert(priority_rr->queue, task, cmpfunc);
}

void run_priority_rr(void) {
    pthread_mutex_lock(&priority_rr->lock);
    current_task = extract_min(priority_rr->queue, cmpfunc);
    while (1) {
        while (atomic_load(&priority_rr->preempt_flag) == 1) {
            pthread_cond_wait(&priority_rr->cond, &priority_rr->lock);
        }

        priority_rr->current_task = current_task;
        printf("Task %s is running with priority = %d and  burst = %d\n", current_task->name, current_task->priority, current_task->burst);

    }
    pthread_mutex_unlock(&priority_rr->lock);
}

void schedule_priority_rr_preempt(void *arg) {
    int current_burst;
    int new_burst;

    atomic_store(&priority_rr->preempt_flag, 1);
    pthread_mutex_lock(&priority_rr->lock);

    current_burst = priority_rr->current_task->burst;
    new_burst = current_burst - 1;

    if(current_burst > 1)
        schedule_priority_rr(priority_rr->current_task);
    else
        free(current_task);

    current_task = extract_min(priority_rr->queue, cmpfunc);
    pthread_cond_signal(&priority_rr->cond);
    pthread_mutex_unlock(&priority_rr->lock);
}


void init_scheduler() {
  sched_queue_t *queue = malloc(sizeof(sched_queue_t));

  priority_rr = malloc(sizeof(scheduler));
  cross_platform_timer_t *timer =malloc(sizeof(cross_platform_timer_t));
  *priority_rr = (scheduler){
      .schedule = schedule_priority_rr,
      .schedule_preempt = schedule_priority_rr_preempt,
      .queue = queue,
      .run = run_priority_rr,
      .timer = timer,
  };

  start_timer(timer, 1, schedule_priority_rr_preempt, NULL);

}
