#pragma once
#include <execution/defines/opaque/opaque.h>

synapse_execution_opaque_declare
	(synapse_execution_sched_entity)

synapse_execution_opaque_declare
	(synapse_execution_sched_task)

typedef struct synapse_execution_sched_traits
{
	synapse_execution_sched_entity
		hnd_sched;

	void
		(*execute_once)
			(synapse_execution_sched_entity);
	void
		(*execute_multiple)
			(synapse_execution_sched_entity, size_t);
	void
		(*dispatch)
			(synapse_execution_sched_entity, synapse_execution_sched_task);
	synapse_execution_sched_task
		(*dispatch_from_proc)
			(synapse_execution_sched_entity, void(*)(void*), void*);
	
} synapse_execution_sched_traits;