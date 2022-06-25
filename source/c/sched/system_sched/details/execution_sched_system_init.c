#include <execution/sched/system_sched/details/execution_sched_system_init.h>

__synapse_execution_sched_system*
__synapse_execution_sched_system_initialize
	(synapse_memory_pooling_dynamic_traits* pMpool)
{
	__synapse_execution_sched_system* ptr_sched
		= malloc(sizeof(__synapse_execution_sched_system));

	ptr_sched->hnd_sched
		= CreateIoCompletionPort
			(INVALID_HANDLE_VALUE, 0, ptr_sched, 0);
	ptr_sched->ptr_mpool
		= pMpool;

	return ptr_sched;
}

void
__synapse_execution_sched_system_cleanup
	(__synapse_execution_sched_system* pSched)
{
	CloseHandle
		(pSched->hnd_sched);
}