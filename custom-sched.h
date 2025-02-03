#ifndef sched
#define sched

#include "queue.h"
#include "task.h"
#include <stdatomic.h>
typedef struct {
  void (*schedule)(Task *);
  void (*schedule_preempt)(void *);
  void (*run)(void);
  sched_queue_t *queue;
  atomic_int preempt_flag;
  Task *current_task;
  pthread_mutex_t lock;
  pthread_cond_t cond;
} scheduler;

void register_scheduler(scheduler *);
#endif // !schedule
