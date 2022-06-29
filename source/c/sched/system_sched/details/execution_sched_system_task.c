#include <execution/sched/system_sched/details/execution_sched_system_task.h>

__synapse_execution_sched_task*
__synapse_execution_sched_system_task_initialize
	(__synapse_execution_sched_system* pSched, void(*pExec)(void*), void* pParam)
{
	__synapse_execution_sched_task
		*ptr_task;
	synapse_memory_pooling_dynamic_chunk
		 ptr_task_mpool;

	do
	{
		ptr_task_mpool = pSched->ptr_mpool->allocate
							(pSched->ptr_mpool->hnd_traits, NULL);

		if(!synapse_execution_opaque_valid(ptr_task_mpool))
			pSched->ptr_mpool->expand_size
				(pSched->ptr_mpool->hnd_traits,
				 pSched->ptr_mpool->current_size(pSched->ptr_mpool->hnd_traits) * 2);
		
	} while (!synapse_execution_opaque_valid(ptr_task_mpool));

	ptr_task
		= pSched->ptr_mpool->retrieve_pointer
			(ptr_task_mpool);

	ptr_task->task_exec_ptr
		= pExec;
	ptr_task->task_exec_param
		= pParam;
	ptr_task->task_exec_chunk
		= ptr_task_mpool;

	return ptr_task;
}

void
__synapse_execution_sched_system_task_cleanup
	(__synapse_execution_sched_system* pSched, __synapse_execution_sched_task* pTask)
{
	pTask->task_exec_ptr
		= NULL;
	pTask->task_exec_param
		= NULL;

	pSched->ptr_mpool->deallocate
		(pSched->ptr_mpool->hnd_traits, pTask->task_exec_chunk);
}