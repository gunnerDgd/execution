#include <execution/io_sched/details/iosched_handle_init.h>

__synapse_execution_io_handle*
    __synapse_execution_io_handle_initialize_from_tcp
        (__synapse_execution_io_sched* pIoSched,
         __synapse_networking_tcp*     pTcp)
{
    __synapse_execution_io_handle*
        ptr_io_handle
            = synapse_system_allocate
                    (sizeof(__synapse_execution_io_handle));
    
    ptr_io_handle->ptr_io_handle_tcp
        = pTcp;
    pIoSched->hnd_io_sched
        = CreateIoCompletionPort
                (pTcp->hnd_tcp_socket,
                    pIoSched->hnd_io_sched, pIoSched, 0);
    return
        ptr_io_handle;
}

__synapse_execution_io_handle*
    __synapse_execution_io_handle_initialize_from_file
        (__synapse_execution_io_sched* pIoSched,
         __synapse_filesystem_file*    pFile)
{
    __synapse_execution_io_handle*
        ptr_io_handle
            = synapse_system_allocate
                    (sizeof(__synapse_execution_io_handle));
    
    ptr_io_handle->ptr_io_handle_file
        = pFile;
    pIoSched->hnd_io_sched
        = CreateIoCompletionPort
                (pFile->hnd_file,
                    pIoSched->hnd_io_sched, pIoSched, 0);
    return
        ptr_io_handle;
}

void
    __synapse_execution_io_handle_cleanup_from_tcp
        (__synapse_execution_io_handle* pTcp)
{
    __synapse_networking_tcp_cleanup
        (pTcp->ptr_io_handle_tcp);
    synapse_system_deallocate
        (pTcp);
}

void
    __synapse_execution_io_handle_cleanup_from_file
        (__synapse_execution_io_handle* pFile)
{
    __synapse_filesystem_file_cleanup
        (pFile->ptr_io_handle_file);
    synapse_system_deallocate
        (pFile);
}