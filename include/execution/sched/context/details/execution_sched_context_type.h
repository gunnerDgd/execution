#pragma once
#include <context/traits/default/default.h>
#include <execution/traits/sched/sched_queue_traits.h>

#include <memory/pooling/dynamic_pooling_traits.h>

#define __synapse_execution_sched_context_task_ended   0
#define __synapse_execution_sched_context_task_standby 1
#define __synapse_execution_sched_context_task_running 2

typedef struct __synapse_execution_sched_context_task
{
	synapse_context_default_entity
		hnd_context_loop,
		hnd_context_this;
	synapse_execution_sched_queue_entity
		hnd_queue_entity;
	synapse_memory_pooling_dynamic_chunk
		hnd_mpool_chunk;

	void(*task_exec)(synapse_context_default_entity, void*);
	void *task_exec_param  ;
	int   task_exec_status ;
} __synapse_execution_sched_context_task;

typedef struct __synapse_execution_sched_context
{
	synapse_execution_sched_queue_traits*
		ptr_queue;
	synapse_memory_pooling_dynamic_traits*
		ptr_mpool;
} __synapse_execution_sched_context;