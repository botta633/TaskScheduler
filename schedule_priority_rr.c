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

// comparing tasks based on their priority
int cmpfunc(const void *a, const void *b){
    struct Node* const * pp1 = a;
    struct Node* const * pp2 = b;
    
    return ((*pp2)->task->priority - (*pp1)->task->priority);

}

//adding the task to the list
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


// Round-Robin scheduling for tasks with the same priority
void runAsRR(struct Node* head){
    
    
    while(head->task->burst > 0){

       //getting the minimum of the time slice and burst time of a task
        int min = ((head->task->burst)+QUANTUM - abs(head->task->burst - QUANTUM))/2;
        run(head->task, min);
        head->task->burst -= min;
        if (head->task->burst == 0)
        {   
             delete(&head, head->task); 
             continue;
        }
        
        head = head->next;

    }  
        
        

    

}

void schedule (struct Node* head){
    struct  Node* temp = head;
    struct Node** ordered_list = malloc(sizeof(struct Node*) * count);
        
    for (int i =0 ; i <count-1; i++) {
        ordered_list[i] = temp;
        temp = temp-> next;
   }
    
    // Ordering based on priority
    ordered_list[count-1] = temp;
    qsort(ordered_list, count, sizeof(struct Node*), cmpfunc);

    //Round-Robin tasks based on their priority 

    for (int i = 0; i < count-1; i++)
    {   
        if (ordered_list[i]->task->priority != ordered_list[i+1]->task->priority)
        {
            run(ordered_list[i]->task, ordered_list[i]->task->burst);
            continue;
        }
        int k = i;
        //making a sub-list of tasks with the same priority,making use of the array that is storing the nodes
        while (ordered_list[i]->task->priority == ordered_list[i+1]->task->priority)
        {
            ordered_list[i]->next = ordered_list[i+1];
            i++;
        } 

        ordered_list[i]->next = ordered_list[k];

        runAsRR(ordered_list[k]);

    }
    
    
 


 
}
    
