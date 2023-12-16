#define _XOPEN_SOURCE 600 // level of compliance with Posix standards
#define _GNU_SOURCE            
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include "threads.h"

#define     SCHDULING_POLICY    SCHED_ASSUMPTION   // options are SCHED_FIFO, SCHED_RR and SCHED_ASSUMPTION

static int n1 = 32180;
static int n2 = 2e3;

static void timespec_add_us(struct timespec *t, long us);

static int timespec_cmp(struct timespec *a, struct timespec *b);

void * thread_100ms(void * args);
void * thread_200ms(void * args);
void * thread_300ms(void * args);


int main(int argc, char **argv)
{
    /* integers used to check calling system call return status*/
    int th1_status, th2_status, th3_status;
    /* Threads IDs*/
    pthread_t thread1, thread2 , thread3; 
    /* Threads attrubuites*/
    pthread_attr_t thread1_attr, thread2_attr, thread3_attr;
    /* Cpu sets*/
    cpu_set_t cpu_set_1, cpu_set_2, cpu_set_3;
    /* Scheduling parameters*/
    struct sched_param scheduling_parameters1, scheduling_parameters2, scheduling_parameters3;

    /* Thread 1 attrubuites*/
    /* Initializing thread attrubuites with the default value*/
    pthread_attr_init(&thread1_attr);
    /* Set inherit-scheduler attribute in thread attributes object to be taken expilicitly from attributes object.*/
    pthread_attr_setinheritsched(&thread1_attr, PTHREAD_EXPLICIT_SCHED);
    #if(SCHDULING_POLICY == SCHED_ASSUMPTION) 
    pthread_attr_setschedpolicy(&thread2_attr, SCHED_FIFO);
    #else
    /* Set attrubuite scheduling policy to scheduling policy choosed*/
    pthread_attr_setschedpolicy(&thread1_attr, SCHDULING_POLICY);
    #endif
    
    /*Clears set, so that it contains no CPUs. */
    CPU_ZERO(&cpu_set_1);
    /* Add CPU 1 to cpu_set_1.*/
    CPU_SET(1,&cpu_set_1);
    /* Set CPU affinity attribute in thread attributes object*/
    pthread_attr_setaffinity_np(&thread1_attr,sizeof(cpu_set_t),&cpu_set_1);
    #if(SCHDULING_POLICY == SCHED_FIFO)
    /* Set schduling priority parameter variable*/
    scheduling_parameters1.sched_priority = 3;
    #elif (SCHDULING_POLICY == SCHED_RR)
    /* Set schduling priority parameter variable*/
    scheduling_parameters1.sched_priority = 3;
    #elif (SCHDULING_POLICY == SCHED_ASSUMPTION)
    /* Set schduling priority parameter variable*/
    scheduling_parameters1.sched_priority = 1;
    #endif
    /* Set schduling priority parameter*/
    pthread_attr_setschedparam(&thread1_attr, &scheduling_parameters1);

    /* Thread 2 attrubuites*/
    /* Initializing thread attrubuites with the default value*/
    pthread_attr_init(&thread2_attr);
    /* Set inherit-scheduler attribute in thread attributes object to be taken expilicitly from attributes object.*/
    pthread_attr_setinheritsched(&thread2_attr, PTHREAD_EXPLICIT_SCHED);
    #if(SCHDULING_POLICY == SCHED_ASSUMPTION) 
    pthread_attr_setschedpolicy(&thread2_attr, SCHED_FIFO);
    #else
    /* Set attrubuite scheduling policy to scheduling policy choosed*/
    pthread_attr_setschedpolicy(&thread2_attr, SCHDULING_POLICY);
    #endif
    
    /*Clears set, so that it contains no CPUs. */
    CPU_ZERO(&cpu_set_2);
    /* Add CPU 1 to cpu_set_2.*/
    CPU_SET(1,&cpu_set_2);
    /* Set CPU affinity attribute in thread attributes object*/
    pthread_attr_setaffinity_np(&thread2_attr,sizeof(cpu_set_t),&cpu_set_2);
    #if(SCHDULING_POLICY == SCHED_FIFO)
    /* Set schduling priority parameter variable*/
    scheduling_parameters2.sched_priority = 2;
    #elif (SCHDULING_POLICY == SCHED_RR)
    /* Set schduling priority parameter variable*/
    scheduling_parameters2.sched_priority = 3;
    #elif (SCHDULING_POLICY == SCHED_ASSUMPTION)
    /* Set schduling priority parameter variable*/
    scheduling_parameters2.sched_priority = 2;
    #endif
    /* Set schduling priority parameter*/
    pthread_attr_setschedparam(&thread2_attr, &scheduling_parameters2);

    /* Thread 3 attrubuites*/
    /* Initializing thread attrubuites with the default value*/
    pthread_attr_init(&thread3_attr);
    /* Set inherit-scheduler attribute in thread attributes object to be taken expilicitly from attributes object.*/
    pthread_attr_setinheritsched(&thread3_attr, PTHREAD_EXPLICIT_SCHED);
    #if(SCHDULING_POLICY == SCHED_ASSUMPTION) 
    pthread_attr_setschedpolicy(&thread2_attr, SCHED_FIFO);
    #else
    /* Set attrubuite scheduling policy to scheduling policy choosed*/
    pthread_attr_setschedpolicy(&thread3_attr, SCHDULING_POLICY);
    #endif
    
    /*Clears set, so that it contains no CPUs. */
    CPU_ZERO(&cpu_set_3);
    /* Add CPU 1 to cpu_set_3.*/
    CPU_SET(1,&cpu_set_3);
    /* Set CPU affinity attribute in thread attributes object*/
    pthread_attr_setaffinity_np(&thread3_attr,sizeof(cpu_set_t),&cpu_set_3);
    #if(SCHDULING_POLICY == SCHED_FIFO)
    /* Set schduling priority parameter variable*/
    scheduling_parameters3.sched_priority = 1;
    #elif (SCHDULING_POLICY == SCHED_RR)
    /* Set schduling priority parameter variable*/
    scheduling_parameters3.sched_priority = 3;
    #elif (SCHDULING_POLICY == SCHED_ASSUMPTION)
    /* Set schduling priority parameter variable*/
    scheduling_parameters3.sched_priority = 3;
    #endif
    /* Set schduling priority parameter*/
    pthread_attr_setschedparam(&thread3_attr, &scheduling_parameters3);



    /* Creating three threads*/
    th1_status = pthread_create(&thread1, &thread1_attr, thread_100ms, NULL);
    th2_status = pthread_create(&thread2, &thread2_attr, thread_200ms, NULL);
    th3_status = pthread_create(&thread3, &thread3_attr, thread_300ms, NULL);
    
    /* Checking Creting error status*/
    if(th1_status || th2_status || th3_status)
    {   /* Error occured*/
        printf("Error while creating threads\n");
    }

    /* Destroying threads attrubuites*/
    pthread_attr_destroy(&thread1_attr);
    pthread_attr_destroy(&thread2_attr);
    pthread_attr_destroy(&thread3_attr);
    
    th1_status = pthread_join(thread1, NULL);
    th2_status = pthread_join(thread2, NULL);
    th3_status = pthread_join(thread3, NULL);

    /* Checking joining threads error status*/
    if(th1_status || th2_status || th3_status)
    {   /* Error occured*/
        printf("Error while waiting on joinable threads\n");
    }

    return 0;
}



void *thread_100ms(void *args)
{
    /* Used to hold curret time instance and next wakeup time respectively*/
    struct timespec current_time, next_wakeup_time;
    /* Loops counters*/
    int i, j;
    /* Dummy var*/
    int a;
    /* Thread period in micosecond*/
    long thread_period_us = 1e5; // 1e5 microseconds = 1e2 milliseconds
    /* Get the current time instance and put it on next_wakeup_time variable*/
    clock_gettime(CLOCK_MONOTONIC, &next_wakeup_time);

    for (;;)
    {
        /* Add period time to the next_wakeup_time var */
        timespec_add_us(&next_wakeup_time, thread_period_us);

        /* Thread main code*/
        /* Simulating thread CPU utilization*/
        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < n2; j++)
                a = j / 2;
        }

        /* Checking Deadline violating criteria*/
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        if ((current_time.tv_sec > next_wakeup_time.tv_sec) || (current_time.tv_sec == next_wakeup_time.tv_sec && current_time.tv_nsec > next_wakeup_time.tv_nsec))
        {
            /* Deadline missed*/
            printf("100ms periodic thread deadline is missed\n");
        }
        else
        {
            printf("100ms periodic thread deadline is met\n");
        }

        /* Making the thread enter sleep state for absloute time defined in next_wakeup_time var*/
        if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_wakeup_time, NULL) != 0)
        { /* error occured*/
            printf("error while executing clock_nanosleep() syscall\n");
        }
    }
    /* Unreacheable(Thread should never return in the case of preiodic thread)*/
}

void *thread_200ms(void *args)
{
    /* Used to hold curret time instance and next wakeup time respectively*/
    struct timespec current_time, next_wakeup_time;
    /* Loops counters*/
    int i, j;
    /* Dummy var*/
    int a;
    /* Thread period in micosecond*/
    long thread_period_us = 2e5; // 1e5 microseconds = 1e2 milliseconds
    /* Get the current time instance and put it on next_wakeup_time variable*/
    clock_gettime(CLOCK_MONOTONIC, &next_wakeup_time);

    for (;;)
    {
        /* Add period time to the next_wakeup_time var */
        timespec_add_us(&next_wakeup_time, thread_period_us);

        /* Thread main code*/
        /* Simulating thread CPU utilization*/
        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < n2; j++)
                a = j / 2;
        }

        /* Checking Deadline violating criteria*/
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        if ((current_time.tv_sec > next_wakeup_time.tv_sec) || (current_time.tv_sec == next_wakeup_time.tv_sec && current_time.tv_nsec > next_wakeup_time.tv_nsec))
        {
            /* Deadline missed*/
            printf("200ms periodic thread deadline is missed\n");
        }
        else
        {
            printf("200ms periodic thread deadline is met\n");
        }

        /* Making the thread enter sleep state for absloute time defined in next_wakeup_time var*/
        if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_wakeup_time, NULL) != 0)
        { /* error occured*/
            printf("error while executing clock_nanosleep() syscall\n");
        }
    }
    /* Unreacheable(Thread should never return in the case of preiodic thread)*/
}

void *thread_300ms(void *args)
{
    /* Used to hold curret time instance and next wakeup time respectively*/
    struct timespec current_time, next_wakeup_time;
    /* Loops counters*/
    int i, j;
    /* Dummy var*/
    int a;
    /* Thread period in micosecond*/
    long thread_period_us = 3e5; // 1e5 microseconds = 1e2 milliseconds
    /* Get the current time instance and put it on next_wakeup_time variable*/
    clock_gettime(CLOCK_MONOTONIC, &next_wakeup_time);

    for (;;)
    {
        /* Add period time to the next_wakeup_time var */
        timespec_add_us(&next_wakeup_time, thread_period_us);

        /* Thread main code*/
        /* Simulating thread CPU utilization*/
        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < n2; j++)
                a = j / 2;
        }

        /* Checking Deadline violating criteria*/
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        if ((current_time.tv_sec > next_wakeup_time.tv_sec) || (current_time.tv_sec == next_wakeup_time.tv_sec && current_time.tv_nsec > next_wakeup_time.tv_nsec))
        {
            /* Deadline missed*/
            printf("300ms periodic thread deadline is missed\n");
        }
        else
        {
            printf("300ms periodic thread deadline is met\n");
        }

        /* Making the thread enter sleep state for absloute time defined in next_wakeup_time var*/
        if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_wakeup_time, NULL) != 0)
        { /* error occured*/
            printf("error while executing clock_nanosleep() syscall\n");
        }
    }
    /* Unreacheable(Thread should never return in the case of preiodic thread)*/
}

static void timespec_add_us(struct timespec *t, long us)
{
    if (us > 1e6)
    {
        printf("Uncorrect use of timespec_add_us() function\n");
    }
    t->tv_nsec += us * 1000;
    if (t->tv_nsec > 1000000000)
    {
        t->tv_nsec = t->tv_nsec - 1000000000;
        t->tv_sec += 1;
    }
}

static int timespec_cmp(struct timespec *a, struct timespec *b)
{
    if (a->tv_sec > b->tv_sec)
        return 1;
    else if (a->tv_sec < b->tv_sec)
        return -1;
    else if (a->tv_sec == b->tv_sec)
    {
        if (a->tv_nsec > b->tv_nsec)
            return 1;
        else if (a->tv_nsec == b->tv_nsec)
            return 0;
        else
            return -1;
    }
}