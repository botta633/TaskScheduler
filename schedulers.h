//
//  schedulers.h
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#ifndef schedulers_h
#define schedulers_h
#include "queue.h"
#define MAX_PRIORITY 10
#define MIN_PRIORITY 1


void add(struct Node** head, char *name, int priority, int burst); //adding a task 

void schedule();
void scheduler_preempt(void);
Task* pick_next_task(struct Node *head);


#endif /* schedulers_h */
