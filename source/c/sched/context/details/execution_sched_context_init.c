#include <execution/sched/context/details/execution_sched_context_init.h>
#include <stdlib.h>

__synapse_execution_sched_context*
__synapse_execution_sched_context_initialize
	(synapse_memory_pooling_dynamic_traits *pMpool, 
	 synapse_execution_sched_queue_traits  *pQueue)
{
	__synapse_execution_sched_context* ptr_sched
		= malloc(sizeof(__synapse_execution_sched_context));

	ptr_sched->ptr_mpool
		= pMpool;
	ptr_sched->ptr_queue
		= pQueue;

	return ptr_sched;
}

void
__synapse_execution_sched_context_cleanup
	(__synapse_execution_sched_context* pSched)
{
	free(pSched);
}