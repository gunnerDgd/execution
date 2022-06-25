#include <execution/sched/system_sched/syssched_init.h>
#include <execution/sched/system_sched/details/execution_sched_system_init.h>

synapse_execution_sched_system
synapse_execution_sched_system_initialize
	(synapse_memory_pooling_dynamic_traits* pMpool)
{
	synapse_execution_opaque_init
		(synapse_execution_sched_system, ptr_sched,
		 __synapse_execution_sched_system_initialize(pMpool));

	return ptr_sched;
}

void
synapse_execution_sched_system_cleanup
	(synapse_execution_sched_system pSched)
{
	__synapse_execution_sched_system_cleanup
		(synapse_execution_opaque_reference(pSched));
}