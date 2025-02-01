//
//  schedule_sjf.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "schedulers.h"
#include "linkedlist.h"
#include "CPU.h"


 //comparing tasks based on their burst time
int cmpfunc(const void *a, const void *b){
    struct Node* const * pp1 = a;
    struct Node* const * pp2 = b;
    
    return ((*pp1)->task->burst - (*pp2)->task->burst);

}


//TODO-----> THREADS!!
//PREEMPTION!!
//Timer

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
    printf("%d\n",count);
    struct  Node* temp = head;
    struct Node** ordered_list = malloc(sizeof(struct Node*) * count);
    // copying Nodes to the array
    for (int i =0 ; i <count-1; i++) {
        ordered_list[i] = temp;
        temp = temp-> next;
    }
    
    
    ordered_list[count-1] = temp;
    // sorting the array of node based on burst time
    qsort(ordered_list, count, sizeof(struct Node*), cmpfunc);
    
 
    for (int i = 0; i < count; i++)
        run(ordered_list[i]->task, ordered_list[i]->task->burst);
    
 
}
	
