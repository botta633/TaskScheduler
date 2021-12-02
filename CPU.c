//
//  CPU.c
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#include "CPU.h"



void run(Task* task, int slice){
    printf("Running task = [%s] [%d] [%d] for %d units.\n", task->name, task->priority, task->burst, slice);
}

