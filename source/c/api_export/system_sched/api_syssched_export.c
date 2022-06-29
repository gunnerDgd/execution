#include <execution/api_export/system_sched/api_syssched_export.h>
#include <execution/sched/system_sched/syssched.h>

#include <stdlib.h>

synapse_execution_sched_traits*
synapse_api_syssched_initialize
	(synapse_memory_pooling_dynamic_traits* pMpool)
{
	synapse_execution_sched_traits* ptr_sched
		= malloc(sizeof(synapse_execution_sched_traits));

	ptr_sched->dispatch
		= &synapse_api_syssched_dispatch;
	ptr_sched->dispatch_from_proc
		= &synapse_api_syssched_dispatch_from_proc;
	
	ptr_sched->execute_multiple
		= &synapse_api_syssched_execute_multiple;
	ptr_sched->execute_once
		= &synapse_api_syssched_execute_once;

	ptr_sched->hnd_sched.opaque
		= synapse_execution_sched_system_initialize(pMpool).opaque;
}

void
synapse_api_syssched_cleanup
	(synapse_execution_sched_traits* pSched)
{
	synapse_execution_sched_system ptr_sched
		= { .opaque = pSched->hnd_sched.opaque };

	synapse_execution_sched_system_cleanup
		(ptr_sched);
	free
		(pSched);
}

void
synapse_api_syssched_dispatch
	(synapse_execution_sched_entity pSched, synapse_execution_sched_task pSchedTask)
{
	synapse_execution_sched_system		ptr_sched
		= { .opaque = pSched.opaque };
	synapse_execution_sched_system_task ptr_sched_task
		= { .opaque = pSchedTask.opaque };

	synapse_execution_sched_system_dispatch
		(ptr_sched, ptr_sched_task);
}

synapse_execution_sched_task
synapse_api_syssched_dispatch_from_proc
	(synapse_execution_sched_entity pSched, void(*pSchedProc)(void*), void* pSchedProcParam)
{
	synapse_execution_sched_system		ptr_sched
		= { .opaque = pSched.opaque };
	synapse_execution_sched_task		ptr_sched_task
		= { .opaque = synapse_execution_sched_system_task_initialize
							(ptr_sched, pSchedProc, pSchedProcParam).opaque };

	synapse_api_syssched_dispatch
		(pSched, ptr_sched_task);
	return
		ptr_sched_task;
}

void
synapse_api_syssched_execute_once
	(synapse_execution_sched_entity pSched)
{
	synapse_execution_sched_system ptr_sched
		= { .opaque = pSched.opaque };

	synapse_execution_sched_system_execute_once
		(ptr_sched);
}

void
synapse_api_syssched_execute_multiple
	(synapse_execution_sched_entity pSched, size_t pCount)
{
	synapse_execution_sched_system ptr_sched
		= { .opaque = pSched.opaque };

	synapse_execution_sched_system_execute_multiple
		(ptr_sched, pCount);
}