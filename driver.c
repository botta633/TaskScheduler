//
//  main.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 20/01/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CPU.h"
#include "schedulers.h"
#include "task.h"
#include "linkedlist.h"



#define SIZE 100

int main(int argc, const char * argv[]) {
    FILE *in; //input file
    char *temp; //temporary char to read the input by char
    char task[SIZE];
    struct Node* head = NULL; //defining the head node
    // variables to hold the data members of struct task
    char *name;
    int priority;
    int burst;
    
    in =fopen(argv[1], "r"); //opening the input file  
    
    
    //parsing the input file 
    while (fgets(task, SIZE, in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp, ",");
        priority = atoi(strsep(&temp, ","));
        burst = atoi(strsep(&temp, ","));
        add(&head,name, priority, burst);
        free(temp);
    }


    fclose(in);

    // if there is only one taske

    if (head->next== head)
        run(head->task, head->task->burst);
    
    //more than one task
    else
        schedule(head);
    
    return 0;
}
