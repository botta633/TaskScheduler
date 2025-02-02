#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#else
#include <pthread.h>
#include <signal.h>
#include <string.h>
#endif

typedef void (*timer_callback)(void *arg);

typedef struct {
#ifdef __APPLE__
  dispatch_source_t timer;
#else
  timer_t timer;
#endif
  timer_callback callback;
  void *callback_args;

} cross_platform_timer_t;

bool start_timer(cross_platform_timer_t *t, double interval_sec,
                 timer_callback cb, void *arg);
void stop_timer(cross_platform_timer_t *t);

#endif
