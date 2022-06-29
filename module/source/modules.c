#include <modules.h>
#include <Windows.h>

HMODULE
	__synapse_execution_module_sched,
	__synapse_execution_module_sched_context;

synapse_modules_export
void synapse_module_entry() {}

synapse_modules_export
void 
synapse_module_initialize
	(synapse_modules_interface* pInterface)
{
	__synapse_execution_module_sched
		= LoadLibraryA("./synapse-context-sched.dll");
	__synapse_execution_module_sched_context
		= LoadLibraryA("./synapse-context-sched-context.dll");

	pInterface->attach
		= &synapse_execution_module_attach;
	pInterface->detach
		= &synapse_execution_module_detach;
	pInterface->reload
		= &synapse_execution_module_reload;
}

synapse_modules_export
void
synapse_module_cleanup
	()
{
	FreeLibrary
		(__synapse_execution_module_sched);
	FreeLibrary
		(__synapse_execution_module_sched_context);
}

void 
synapse_execution_module_attach
	(synapse_modules_handle pHandle, void* pParameter) {}

void 
synapse_execution_module_detach
	(synapse_modules_handle pHandle, void* pParameter) {}

void
synapse_execution_module_reload
	(synapse_modules_handle pHandle, void* pParameter) {}