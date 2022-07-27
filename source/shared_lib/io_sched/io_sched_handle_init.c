#include <execution/export/io_sched/io_sched_handle_init.h>
#include <execution/io_sched/io_sched_handle_init.h>

synapse_execution_dll
    synapse_io_schedule_handle_file
        synapse_initialize_io_handle_from_file
            (synapse_execution_io_sched pIoSched, synapse_file_aio pAioFile)
{
    return
        synapse_execution_io_handle_initialize_from_file
            (pIoSched, pAioFile);
}

synapse_execution_dll
    synapse_io_schedule_handle_tcp
        synapse_initialize_io_handle_from_tcp
            (synapse_execution_io_sched pIoSched, synapse_tcp_aio pAioTcp)
{
    return
        synapse_execution_io_handle_initialize_from_tcp
            (pIoSched, pAioTcp);
}

synapse_execution_dll
    void
        synapse_cleanup_io_handle_file
            (synapse_io_schedule_handle_file pFile)
{
    synapse_execution_io_handle_file_cleanup
        (pFile);
}

synapse_execution_dll
    void
        synapse_cleanup_io_handle_tcp
            (synapse_io_schedule_handle_tcp pTcp)
{
    synapse_execution_io_handle_tcp_cleanup
        (pTcp);
}