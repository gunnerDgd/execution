#include <execution/sched/system_sched/syssched_task.h>
#include <execution/sched/system_sched/details/execution_sched_system_task.h>

synapse_execution_sched_system_task
synapse_execution_sched_system_task_initialize
	(synapse_execution_sched_system pSched, void(*pExec)(void*), void* pExecParam)
{
	synapse_execution_opaque_init
		(synapse_execution_sched_system_task,
		 ptr_task,
		 __synapse_execution_sched_system_task_initialize
			(synapse_execution_opaque_reference(pSched), pExec, pExecParam)
		);

	return ptr_task;
}

void
synapse_execution_sched_system_task_cleanup
	(synapse_execution_sched_system pSched, synapse_execution_sched_system_task pTask)
{
	__synapse_execution_sched_system_task_cleanup
		(synapse_execution_opaque_reference(pSched),
		 synapse_execution_opaque_reference(pTask));
}