#pragma once

#ifdef synapse_execution_export_mode
#define synapse_execution_export _declspec(dllexport)
#else
#define synapse_execution_export _declspec(dllimport)
#endif