//
//  schedule_rr.c
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
    //getting the minimum of task burst time and the time slice
    int min = ((head->task->burst)+QUANTUM - abs(head->task->burst - QUANTUM))/2;

    run(head->task, min);
    head->task->burst -=min; 
    
    if (head->task->burst <= 0)
        delete(&head, head->task);
    
    // running tasks in RR making use of the circular linked list
    while(head ->next != head){
       
        min = ((head->task->burst)+QUANTUM - abs(head->task->burst - QUANTUM))/2;
        run(head->task, min);
        head->task->burst -= min;
        if (head->task->burst == 0)
        {   
             delete(&head, head->task); 
             continue;
        }
        
        head = head->next;
 
    }
    run(head->task, head->task->burst);
    delete(&head, head->task);

}


 
