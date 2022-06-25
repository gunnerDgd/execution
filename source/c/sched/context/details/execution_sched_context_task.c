#include <execution/sched/context/details/execution_sched_context_task.h>

__synapse_execution_sched_context_task*
__synapse_execution_sched_context_task_initialize
	(__synapse_execution_sched_context* pSched,
	 void(*pExecPtr)(synapse_context_default_entity, void*), 
	 void *pExecParam)
{
	__synapse_execution_sched_context_task* ptr_task;
	synapse_memory_pooling_dynamic_chunk    ptr_task_chk
		= pSched->ptr_mpool->allocate
			(pSched->ptr_mpool->hnd_traits, NULL);

	ptr_task
		= pSched->ptr_mpool->retrieve_pointer
			(ptr_task_chk);

	ptr_task->hnd_mpool_chunk
		= ptr_task_chk;
	ptr_task->task_exec
		= pExecPtr;
	ptr_task->task_exec_param
		= pExecParam;

	return
		ptr_task;
}

void
__synapse_execution_sched_context_task_cleanup
	(__synapse_execution_sched_context	    *pSched, 
	 __synapse_execution_sched_context_task *pTask)
{
	pTask->hnd_context_this
		= synapse_context_default_initialize_from_existing(pTask->hnd_context_this);
	pTask->task_exec
		= NULL;
	pTask->task_exec_param
		= NULL;

	pSched->ptr_mpool->deallocate
		(pSched->ptr_mpool->hnd_traits, pTask->hnd_mpool_chunk);
}