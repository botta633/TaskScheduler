//
//  CPU.h
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#ifndef CPU_h
#define CPU_h

#include <stdio.h>
#include "task.h"
#define QUANTUM 10

// function to simulate the running of tasks
void run(Task* task, int slice);

#endif /* CPU_h */
