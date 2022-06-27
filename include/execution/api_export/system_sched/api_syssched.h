#pragma once
#include <modules/traits/modman_interface.h>
#include <execution/traits/sched/sched_traits.h>

_declspec(dllexport)
void synapse_module_initialize
	(synapse_modules_interface*);

_declspec(dllexport)
void synapse_module_cleanup();

_declspec(dllexport)
void synapse_module_entry
	(synapse_modules_handle);

_declspec(dllexport)
void synapse_execution_syssched_api_attach
	(synapse_modules_handle, synapse_execution_sched_traits*);

_declspec(dllexport)
void synapse_execution_syssched_api_detach
	(synapse_modules_handle, synapse_execution_sched_traits*);

_declspec(dllexport)
void synapse_execution_syssched_api_reload
	(synapse_modules_handle, synapse_execution_sched_traits*);