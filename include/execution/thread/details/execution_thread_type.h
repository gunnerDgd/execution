#pragma once

#include <Windows.h>
#include <process.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <synapse/structure/queue/lockfree/mpmc.h>

#define __synapse_execution_thread_queue_default 256
#define __synapse_execution_thread_loop_begin    while(true) {
#define __synapse_execution_thread_loop_end      }

typedef struct
    __synapse_execution_thread_task
{
    void
        (*ptr_thread_task)(void*);
    void *ptr_thread_task_parameter;
} __synapse_execution_thread_task;

typedef struct
    __synapse_execution_thread
{
    HANDLE
        hnd_thread,
        hnd_thread_execution_event;
    synapse_mpmc_queue
        hnd_thread_queue; 
} __synapse_execution_thread;