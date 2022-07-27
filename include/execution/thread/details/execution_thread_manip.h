#pragma once
#include <execution/thread/details/execution_thread_type.h>

void
    __synapse_execution_thread_dispatch
        (__synapse_execution_thread*,
                void(*)(void*), void*);

void
    __synapse_execution_thread_wait
        (__synapse_execution_thread*);

bool
    __synapse_execution_thread_wait_until
        (__synapse_execution_thread*, uint32_t);