//
//  schedulers.h
//  task_scheduler
//
//  Created by ahmed ehab hamouda on 21/01/2021.
//

#ifndef schedulers_h
#define schedulers_h
#include "pq.h"
#define MAX_PRIORITY 10
#define MIN_PRIORITY 1

struct scheduler {
    void (*schedule)(Task *);
};

static pq_t *q;


#endif /* schedulers_h */
