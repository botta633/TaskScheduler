//
//  linkedlist.h
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 20/01/2021.
//

#ifndef linkedlist_h
#define linkedlist_h

#include "task.h"


struct Node{
    struct Node* next;
    struct Node *prev;
    Task *task;
    
};

extern int count; //a variable to count the number of nodes

void append(struct Node** head, Task* task); //add a Node to the end of the list
void push(struct Node **head, Task* task); // add a Node to the begging of the list 
void delete(struct Node **head, Task* task); //deleting a task from the list
void traverse(struct Node *head); // traversing the list







#endif /* linkedlist_h */
