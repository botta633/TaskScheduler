//
//  linkedlist.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 20/01/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


 int count = 0;

// pushing a task to the beginning of the list
void push(struct Node **head, Task* newtask)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->task = newtask;
    new_node->next = *head;
    *head = newnode;
}


void delete(struct Node** head, Task* task){
    struct Node* last = NULL;
    
    
    struct Node* temp;
    struct Node* prev;

    if (count == 1)
    {
        *head = NULL;
    }
    

    //if the task is at the beginning of the list
    temp = *head;
    while((temp)->next != *head){
        temp= temp->next;
    }
    last = temp;
    last->next = *head;
    temp = *head;
    
    if (strcmp(task->name, temp->task->name) == 0){
        last ->next = (*head)->next;
        *head = (*head)->next;
}

    //if the task is in the middle or the last element of the list
    else{
        prev = *head;
        temp = temp->next;
        while(strcmp(task->name, temp->task->name) != 0){
            prev = temp;
            temp = temp->next;

        }
        prev->next = temp->next;
    }

}

void append(struct Node** head, Task* task){
    struct Node *newnode =  NULL;
    struct Node* last= NULL;

    newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode ->task = task;

    if (newnode == NULL) {
        printf("No enough memory \n");
        return;
    }
    // beginning of the list
    if (*head == NULL) {
        *head = newnode;
        (*head)->next = *head;
        count++;
        return;
    }
    // end of list
    last = *head;

    while (last -> next != *head) {
        last = last ->next;
    }

    last -> next = newnode;
    //making the list circular
    newnode ->next = *head;

    count++;
   	
}





void print_task(Task * task){
    printf("[%s] [%d] [%d]\n", task->name, task->priority, task->burst);
}


void traverse(struct Node * head){
    struct Node*temp;
    temp = head;
    do {
        print_task(temp->task);
        temp = temp -> next;
    } while(temp != head);
}






