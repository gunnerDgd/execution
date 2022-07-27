#pragma once

#include <Windows.h>
#include <process.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define __synapse_execution_thread_state_standby 0
#define __synapse_execution_thread_state_running 1
#define __synapse_execution_thread_state_stopped 2

typedef struct
    __synapse_execution_thread
{
    HANDLE
          hnd_thread,
          hnd_thread_execution_event;
    void
        (*ptr_thread_exec)(void*);
    void
         *ptr_thread_exec_param;
    volatile uint8_t
          flag_thread_execution;
} __synapse_execution_thread;