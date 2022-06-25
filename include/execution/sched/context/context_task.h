#pragma once
#include <execution/sched/context/context_type.h>

synapse_execution_sched_context_task
synapse_execution_sched_context_task_initialize
	(synapse_execution_sched_context, 
	 void(*)(synapse_context_default_entity, void*), void*);

void
synapse_execution_sched_context_task_cleanup
	(synapse_execution_sched_context,
	 synapse_execution_sched_context_task);