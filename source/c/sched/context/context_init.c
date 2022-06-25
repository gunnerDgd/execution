#include <execution/sched/context/context_init.h>
#include <execution/sched/context/details/execution_sched_context_init.h>

synapse_execution_sched_context
synapse_execution_sched_context_initialize
	(synapse_memory_pooling_dynamic_traits *pMpool, 
	 synapse_execution_sched_queue_entity  *pQueue)
{
	synapse_execution_opaque_init
		(synapse_execution_sched_context,
		 ptr_sched,
		 __synapse_execution_sched_context_initialize
			(pMpool, pQueue));

	return
		ptr_sched;
}

void
synapse_execution_sched_context_cleanup
	(synapse_execution_sched_context pSched)
{
	__synapse_execution_sched_context_cleanup
		(synapse_execution_opaque_reference(pSched));
}