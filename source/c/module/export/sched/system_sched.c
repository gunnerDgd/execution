#include <execution/module/export/sched/system_sched.h>
#include <execution/sched/system_sched/details/execution_sched_system_type.h>

#include <stdlib.h>

synapse_modules_component_interface
	synapse_execution_syssched_export
		()
{
	synapse_modules_component_interface
		hnd_component
			= {
				.construct
					= &synapse_execution_syssched_export_construct,
				.destruct
					= &synapse_execution_syssched_export_destruct,
				.duplicate
					= &synapse_execution_syssched_export_duplicate
			  };

	return
		hnd_component;
}

void*
	synapse_execution_syssched_export_construct
		(va_list pArgList)
{
	synapse_execution_sched_traits*
		ptr_traits
			= malloc(sizeof(synapse_execution_sched_traits));

	ptr_traits->hnd_sched
		= synapse_execution_sched_system_initialize
				(va_arg(pArgList, synapse_memory_pooling_dynamic_traits*));
	
	ptr_traits->dispatch
		= &synapse_execution_sched_system_dispatch;
	ptr_traits->dispatch_from_proc
		= &synapse_execution_sched_system_dispatch_from_proc;

	ptr_traits->execute_once
		= &synapse_execution_sched_system_execute_once;
	ptr_traits->execute_multiple
		= &synapse_execution_sched_system_execute_multiple;

	return
		ptr_traits;
}

void
	synapse_execution_syssched_export_destruct
		(void* pVoidSched)
{
	synapse_execution_sched_system_cleanup
		(((synapse_execution_sched_traits*)pVoidSched)
				->hnd_sched);
	free
		(pVoidSched);
}

void*
	synapse_execution_syssched_export_duplicate
		(void* pVoidSched)
{
	synapse_execution_sched_traits*
		ptr_sched
			= malloc
					(sizeof(synapse_execution_sched_traits));

	ptr_sched->hnd_sched
		= synapse_execution_sched_system_initialize
			(synapse_execution_opaque_cast
				(((synapse_execution_sched_traits*)pVoidSched)
					->hnd_sched, __synapse_execution_sched_system*)
					->ptr_mpool);

	ptr_sched->dispatch
		= &synapse_execution_sched_system_dispatch;
	ptr_sched->dispatch_from_proc
		= &synapse_execution_sched_system_dispatch_from_proc;

	ptr_sched->execute_once
		= &synapse_execution_sched_system_execute_once;
	ptr_sched->execute_multiple
		= &synapse_execution_sched_system_execute_multiple;

	return
		ptr_sched;
}