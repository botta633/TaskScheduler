//
//  schedule_priority.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 23/01/2021.
//

#include "linkedlist.h"
#include "schedulers.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const Task *a, const Task *b) {

  return (a->priority - b->priority);
}

void add(char *name, int priority, int burst) {

  Task *newtask = (struct task *)malloc(sizeof(struct task));
  newtask->name = name;
  newtask->priority = priority;
  newtask->burst = burst;
  insert(q, newtask, cmpfunc);
}
Task *pick_next_task(struct Node *head) { return head->task; }

void schedule(struct Node *head) {
  while (1) {
  }
}
