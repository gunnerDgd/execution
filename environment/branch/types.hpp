#pragma once
#include <iostream>

#define BRANCH_PRESERVE __attribute__((always_inline))

namespace branch  {
namespace context {
    
    class alignas(16) cpu_register // 64 Byte.
    {
    public:
        union
        {
            struct
            {
                uint64_t     rax, rbx, rcx, rdx,
                             rsi, rdi, rip     ; // 56 Byte
            };  uint64_t     register_block[7] ;
        };
    };

    class alignas(16) frame // 16 Byte
    {
    public:
        union
        {
            struct { uint64_t rbp, rsp; }      ;
            uint64_t          stack_register[2];
        };
    };

    struct context_entity
    {
        cpu_register cpu_context  ; // 64
        frame        stack_context; // 16
    };

    enum  execution_state
    {
        standby,
        running,
        stopped
    };

    class execution_wrapper : public context_entity 
    {
    public:
        execution_state get_state () { return executor_state; }
        virtual void    execute   ()                   = 0;

    protected:
        execution_state executor_state;
    };
}
}