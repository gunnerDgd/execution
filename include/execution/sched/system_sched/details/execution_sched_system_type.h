#pragma once
#include <Windows.h>
#include <memory/pooling/dynamic_pooling_traits.h>

typedef struct __synapse_execution_sched_task
{
	OVERLAPPED 
		task_dummy;
	synapse_memory_pooling_dynamic_chunk
		task_exec_chunk;

	void
		(*task_exec_ptr)(void*);
	void *task_exec_param;
} __synapse_execution_sched_task;

typedef struct __synapse_execution_sched_system
{
	HANDLE
		hnd_sched;
	synapse_memory_pooling_dynamic_traits*
		ptr_mpool;
} __synapse_execution_sched_system;