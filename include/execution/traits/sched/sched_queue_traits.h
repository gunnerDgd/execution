#pragma once
#include <stdint.h>
#include <execution/defines/opaque/opaque.h>

synapse_execution_opaque_declare
	(synapse_execution_sched_queue_handle)
	
synapse_execution_opaque_declare
	(synapse_execution_sched_queue_entity)

typedef struct synapse_execution_sched_queue_traits
{
	synapse_execution_sched_queue_handle
		hnd_queue;

	synapse_execution_sched_queue_entity
		(*enqueue_front)
			(synapse_execution_sched_queue_handle, void*, size_t);
	synapse_execution_sched_queue_entity
		(*enqueue_back)
			(synapse_execution_sched_queue_handle, void*, size_t);

	synapse_execution_sched_queue_entity
		(*dequeue_front)
			(synapse_execution_sched_queue_handle);
	synapse_execution_sched_queue_entity
		(*dequeue_back)
			(synapse_execution_sched_queue_handle);

	synapse_execution_sched_queue_entity
		(*move_front)
			(synapse_execution_sched_queue_handle);
	synapse_execution_sched_queue_entity
		(*move_back)
			(synapse_execution_sched_queue_handle);

	void*
		(*retrieve_pointer)
			(synapse_execution_sched_queue_entity);
	size_t
		(*retrieve_size)
			(synapse_execution_sched_queue_entity);
} synapse_execution_sched_queue_traits;