#pragma once
#include <modules/traits/modman_interface.h>

synapse_modules_export
void synapse_module_entry();

synapse_modules_export
void 
synapse_module_initialize
	(synapse_modules_interface*);

synapse_modules_export
void
synapse_module_cleanup
	();

void 
synapse_execution_module_attach
	(synapse_modules_handle, void*);

void 
synapse_execution_module_detach
	(synapse_modules_handle, void*);

void
synapse_execution_module_reload
	(synapse_modules_handle, void*);