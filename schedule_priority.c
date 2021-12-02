//
//  schedule_priority.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 23/01/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "schedulers.h"
#include "linkedlist.h"
#include "CPU.h"


int cmpfunc(const void *a, const void *b){
    struct Node* const * pp1 = a;
    struct Node* const * pp2 = b;
    
    return ((*pp2)->task->priority - (*pp1)->task->priority);

}


void add(struct Node** head, char* name, int priority, int burst){

    Task *newtask = (struct task *)malloc(sizeof(struct task));
    newtask->name = name;
    newtask->priority = priority;
    newtask -> burst = burst;
    append(head, newtask);

}
Task* pick_next_task(struct Node *head){
    return head->task;
}


void schedule (struct Node* head){
    struct  Node* temp = head;
    struct Node** ordered_list = malloc(sizeof(struct Node*) * count);
        
    for (int i =0 ; i <count-1; i++) {
        ordered_list[i] = temp;
        temp = temp-> next;
    }
    
    
    ordered_list[count-1] = temp;
    qsort(ordered_list, count, sizeof(struct Node*), cmpfunc);
    
 
    for (int i = 0; i < count; i++)
        run(ordered_list[i]->task, ordered_list[i]->task->burst);
    
 
}
    
