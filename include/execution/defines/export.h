#pragma once

#ifdef synapse_execution_export_mode
#define synapse_execution_export _declspec(dllexport)
#elif synapse_execution_staticlib_mode
#define synapse_execution_export
#else
#define synapse_execution_export _declspec(dllimport)
#endif