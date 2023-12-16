/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  thread.c
 *  Description:  Source file for thread implementation
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Omar Tolba
 *	Date:		  12/12/2023
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Includes
 *********************************************************************************************************************/
#define _XOPEN_SOURCE 600 // level of compliance with Posix standards
#include <stdio.h>
#include <time.h>

/**********************************************************************************************************************
 *  Static (private) functions prototypes
 *********************************************************************************************************************/
static void timespec_add_us(struct timespec *t, long us);

static int timespec_cmp(struct timespec *a, struct timespec *b);

/**********************************************************************************************************************
 *  Static (private) Vars
 *********************************************************************************************************************/
/* Variables controls Thread cpu utilization*/
static int n1 = 32180;
static int n2 = 2e3;

/**********************************************************************************************************************
 *  Threads implemntations
 *********************************************************************************************************************/
/*******************************************************************************
 * Service Name: thread_100ms
 * Parameters (in):  args - void *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void *
 * Description: 100ms periodic thread
 *******************************************************************************/
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

/*******************************************************************************
 * Service Name: thread_200ms
 * Parameters (in):  args - void *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void *
 * Description: 200ms periodic thread
 *******************************************************************************/
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

/*******************************************************************************
 * Service Name: thread_300ms
 * Parameters (in):  args - void *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void *
 * Description: 300ms periodic thread
 *******************************************************************************/
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

/**********************************************************************************************************************
 *  Static(private) functions implemntations
 *********************************************************************************************************************/
/*******************************************************************************
 * Service Name: thread_100ms
 * Parameters (in): us - long
 * Parameters (inout): t - struct timespec *
 * Parameters (out): None
 * Return value: void
 * Description: add microsecnods to timespec instance
 * Note : that version of the function cannot correctly add more than one second to
the time value
 *******************************************************************************/
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

/*******************************************************************************
 * Service Name: thread_100ms
 * Parameters (in): a - struct timespec *, b- struct timespec *
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: int - returns value of 1 if the first timespec argument has higher
 *                     time value than the second timespec argument
 * Description: Compare two timespec instances
 *******************************************************************************/
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

/**********************************************************************************************************************
 *  END OF FILE: Threads
 * .c
 *********************************************************************************************************************/