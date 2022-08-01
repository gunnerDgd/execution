#pragma once
#include <execution/thread/details/execution_thread_type.h>

__synapse_execution_thread*
    __synapse_execution_thread_initialize
        (size_t);

void
    __synapse_execution_thread_loop
        (__synapse_execution_thread*);

void
    __synapse_execution_thread_cleanup
        (__synapse_execution_thread*);