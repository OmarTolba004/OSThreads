/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Assignemnet.c
 *  Description:  Main source file for ELC-4030 assignment
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Omar Tolba
 *	Date:		  12/12/2023
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  MACRO
 *********************************************************************************************************************/
#define     SCHDULING_POLICY    SCHED_RR   // options are CHED_FIFO,  SCHED_RR,  andSCHED_OTHER
/**********************************************************************************************************************
 *  Includes
 *********************************************************************************************************************/
#define _XOPEN_SOURCE 600 // level of compliance with Posix standards
#define _GNU_SOURCE            
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include "threads.h"

/**********************************************************************************************************************
 *  Main
 *********************************************************************************************************************/
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
    /* Set attrubuite scheduling policy to scheduling policy choosed*/
    pthread_attr_setschedpolicy(&thread1_attr, SCHDULING_POLICY);
    /*Clears set, so that it contains no CPUs. */
    CPU_ZERO(&cpu_set_1);
    /* Add CPU 1 to cpu_set_1.*/
    CPU_SET(1,&cpu_set_1);
    /* Set CPU affinity attribute in thread attributes object*/
    pthread_attr_setaffinity_np(&thread1_attr,sizeof(cpu_set_t),&cpu_set_1);
    /* Set schduling priority parameter variable*/
    scheduling_parameters1.sched_priority = 3;
    /* Set schduling priority parameter*/
    pthread_attr_setschedparam(&thread1_attr, &scheduling_parameters1);

    /* Thread 2 attrubuites*/
    /* Initializing thread attrubuites with the default value*/
    pthread_attr_init(&thread2_attr);
    /* Set inherit-scheduler attribute in thread attributes object to be taken expilicitly from attributes object.*/
    pthread_attr_setinheritsched(&thread2_attr, PTHREAD_EXPLICIT_SCHED);
    /* Set attrubuite scheduling policy to scheduling policy choosed*/
    pthread_attr_setschedpolicy(&thread2_attr, SCHDULING_POLICY);
    /*Clears set, so that it contains no CPUs. */
    CPU_ZERO(&cpu_set_2);
    /* Add CPU 1 to cpu_set_2.*/
    CPU_SET(1,&cpu_set_2);
    /* Set CPU affinity attribute in thread attributes object*/
    pthread_attr_setaffinity_np(&thread2_attr,sizeof(cpu_set_t),&cpu_set_2);
    /* Set schduling priority parameter variable*/
    scheduling_parameters2.sched_priority = 3;
    /* Set schduling priority parameter*/
    pthread_attr_setschedparam(&thread2_attr, &scheduling_parameters2);

    /* Thread 3 attrubuites*/
    /* Initializing thread attrubuites with the default value*/
    pthread_attr_init(&thread3_attr);
    /* Set inherit-scheduler attribute in thread attributes object to be taken expilicitly from attributes object.*/
    pthread_attr_setinheritsched(&thread3_attr, PTHREAD_EXPLICIT_SCHED);
    /* Set attrubuite scheduling policy to scheduling policy choosed*/
    pthread_attr_setschedpolicy(&thread3_attr, SCHDULING_POLICY);
    /*Clears set, so that it contains no CPUs. */
    CPU_ZERO(&cpu_set_3);
    /* Add CPU 1 to cpu_set_3.*/
    CPU_SET(1,&cpu_set_3);
    /* Set CPU affinity attribute in thread attributes object*/
    pthread_attr_setaffinity_np(&thread3_attr,sizeof(cpu_set_t),&cpu_set_3);
    /* Set schduling priority parameter variable*/
    scheduling_parameters3.sched_priority = 3;
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

/**********************************************************************************************************************
 *  END OF FILE: assign.c
 *********************************************************************************************************************/