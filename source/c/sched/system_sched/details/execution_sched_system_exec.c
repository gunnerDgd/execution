#include <execution/sched/system_sched/details/execution_sched_system_exec.h>

void
__synapse_execution_sched_system_dispatch
	(__synapse_execution_sched_system* pSched, __synapse_execution_sched_task* pTask)
{
	PostQueuedCompletionStatus
		(pSched->hnd_sched, 0, pSched, pTask);
}

void
__synapse_execution_sched_system_execute_once
	(__synapse_execution_sched_system* pSched)
{
	DWORD
		sz_dummy;
	__synapse_execution_sched_task*
		ptr_task;

	GetQueuedCompletionStatus
		(pSched->hnd_sched, &sz_dummy, pSched, &ptr_task, INFINITE);

	ptr_task->task_exec_ptr
		(ptr_task->task_exec_param);
}

void
__synapse_execution_sched_system_execute_multiple
	(__synapse_execution_sched_system* pSched, size_t pCount)
{
	while (pCount--)
		__synapse_execution_sched_system_execute_once(pSched);
}