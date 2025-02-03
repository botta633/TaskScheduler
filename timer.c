#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdatomic.h>
#ifdef __APPLE__
#include <dispatch/dispatch.h>


void gcd_timer_callback(void *arg) {
    cross_platform_timer_t *t = (cross_platform_timer_t *)arg;
    if (t->callback) {
        t->callback(t->callback_args);
    }
}

bool start_timer(cross_platform_timer_t *t, double interval_sec, timer_callback cb, void *arg) {
    if (!t) return false;

    t->callback = cb;
    t->callback_args = arg;

    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    t->timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);

    if (!t->timer) return false;

    dispatch_source_set_timer(t->timer, dispatch_time(DISPATCH_TIME_NOW, interval_sec * NSEC_PER_SEC),
                              interval_sec * NSEC_PER_SEC, 0);
    dispatch_source_set_event_handler_f(t->timer, gcd_timer_callback);
    dispatch_set_context(t->timer, t);
    dispatch_resume((dispatch_source_t)t->timer);
    
    return true;
}

void stop_timer(cross_platform_timer_t *t) {
    if (t && t->timer) {
        dispatch_source_cancel((dispatch_source_t)t->timer);
        t->timer = NULL;
    }
}

#else // Linux

#include <signal.h>

void posix_timer_callback(int sig, siginfo_t *si, void *uc) {
    cross_platform_timer_t *t = (cross_platform_timer_t *)si->si_value.sival_ptr;
    if (t->callback) {
        t->callback(t->callback_arg);
    }
}

bool start_timer(cross_platform_timer_t *t, double interval_sec, timer_callback cb, void *arg) {
    if (!t) return false;

    struct sigevent sev;
    struct itimerspec its;
    struct sigaction sa;

    t->callback = cb;
    t->callback_arg = arg;

    memset(&sev, 0, sizeof(sev));
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = t;

    if (timer_create(CLOCK_REALTIME, &sev, (timer_t *)&t->timer) == -1) {
        perror("timer_create");
        return false;
    }

    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = posix_timer_callback;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
        perror("sigaction");
        return false;
    }

    its.it_value.tv_sec = (time_t)interval_sec;
    its.it_value.tv_nsec = (interval_sec - (time_t)interval_sec) * 1e9;
    its.it_interval = its.it_value;

    if (timer_settime((timer_t)t->timer, 0, &its, NULL) == -1) {
        perror("timer_settime");
        return false;
    }

    return true;
}

void stop_timer(cross_platform_timer_t *t) {
    if (t && t->timer) {
        timer_delete((timer_t)t->timer);
        t->timer = NULL;
    }
}

#endif
