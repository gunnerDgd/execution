#include <WinSock2.h>
#include <synapse/memory/pooling/dynamic_pooling.h>

#include <execution/interface/sched/io_sched.h>

#include <networking/tcp/details/tcp_type.h>
#include <filesystem/file/details/fs_file_type.h>

typedef struct
    __synapse_execution_io_handle
{
    union
    {
        __synapse_networking_tcp*
            ptr_io_handle_tcp;
        __synapse_filesystem_file*
            ptr_io_handle_file;
    };
} __synapse_execution_io_handle;

typedef struct
    __synapse_execution_io_task
{
    OVERLAPPED
        hnd_io_task;
    union
    {
        struct
        {
            void*
                ptr_io_task_memory;
            size_t
                size_io_task_memory;
        };
        WSABUF
            hnd_network_buffer;
    };

    size_t
          size_io_task_completion;
    void
        (*ptr_completion_routine)
            (size_t, void*);
    void 
         *ptr_completion_routine_parameter;
} __synapse_execution_io_task;

typedef struct
    __synapse_execution_io_sched
{
    HANDLE
        hnd_io_sched;
} __synapse_execution_io_sched;