#include <execution/io_sched/io_sched_handle_init.h>
#include <execution/io_sched/details/iosched_handle_init.h>

synapse_execution_io_handle_file
    synapse_execution_io_handle_initialize_from_file
        (synapse_execution_io_sched pIoSched,
         synapse_file_aio           pAioFile)
{
    synapse_execution_opaque_init
        (synapse_execution_io_handle_file, hnd_file,
            __synapse_execution_io_handle_initialize_from_file
                (synapse_execution_opaque_reference
                    (pIoSched),
                 synapse_filesystem_opaque_reference
                    (pAioFile)));
    
    synapse_filesystem_opaque_reference
        (pAioFile) = NULL;
    return
        hnd_file;
}

synapse_execution_io_handle_tcp
    synapse_execution_io_handle_initialize_from_tcp
        (synapse_execution_io_sched pIoSched,
         synapse_tcp_aio            pAioTcp)
{
    synapse_execution_opaque_init
        (synapse_execution_io_handle_tcp, hnd_tcp,
            __synapse_execution_io_handle_initialize_from_tcp
                (synapse_execution_opaque_reference
                    (pIoSched),
                 synapse_networking_opaque_reference
                    (pAioTcp)));
    
    synapse_filesystem_opaque_reference
        (pAioTcp) = NULL;
    return
        hnd_tcp;
}

void
    synapse_execution_io_handle_file_cleanup
        (synapse_execution_io_handle_file pIoHandle)
{
    __synapse_execution_io_handle_cleanup_from_file
        (synapse_execution_opaque_reference
            (pIoHandle));
}

void
    synapse_execution_io_handle_tcp_cleanup
        (synapse_execution_io_handle_tcp pIoHandle)
{
    __synapse_execution_io_handle_cleanup_from_tcp
        (synapse_execution_opaque_reference
            (pIoHandle));
}