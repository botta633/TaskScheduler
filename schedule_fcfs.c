//
//  schedule_fcfs.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#include <stdio.h>
#include "task.h"
#include <stdlib.h>

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
    //scheduling tasks according to first come first served
    run(head->task, head->task->burst);
    delete(&head, head->task);
    while(head->next != head){
        Task* new = pick_next_task(head);
        run(new, new->burst);
        delete(&head, head->task);
    }
    run(head->task, head->task->burst);
    delete(&head, head->task);
}









