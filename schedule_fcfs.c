//
//  schedule_fcfs.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#include "task.h"
#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"
#include "linkedlist.h"
#include "schedulers.h"

void add(struct Node **head, char *name, int priority, int burst) {

  Task *newtask = (struct task *)malloc(sizeof(struct task));
  newtask->name = name;
  newtask->priority = priority;
  newtask->burst = burst;
  append(head, newtask);
}
void schedule_fifo(struct Node *head) {
  // scheduling tasks according to first come first served
  run(head->task, head->task->burst);
  delete (&head, head->task);
  while (head->next != head) {
    Task *new = pick_next_task(head);
    run(new, new->burst);
    delete (&head, head->task);
  }
  run(head->task, head->task->burst);
  delete (&head, head->task);
}
