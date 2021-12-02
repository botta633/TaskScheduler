//
//  task.h
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 20/01/2021.
//

#ifndef task_h
#define task_h

typedef struct task{
    int pid;
    char* name;
    int priority;
    int burst;
    
} Task;

void print_task(Task *task);



#endif /* task_h */
