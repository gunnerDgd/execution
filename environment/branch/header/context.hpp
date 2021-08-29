#include <executor/environment/branch/header/types.hpp>

#include <cstring>
#include <tuple>

extern "C"
{
    void context_store_cpu    (branch::context::cpu_register& curr);
    void context_load_cpu     (branch::context::cpu_register& curr);

    void context_capture_stack(branch::context::frame&        curr);
    void context_store_stack  (branch::context::frame&        curr);
    void context_load_stack   (branch::context::frame&        curr);

    void context_switch_to    (branch::context::context_entity& next);
}

namespace branch   {
namespace context  {

namespace internal {
    void switch_to (branch::context::context_entity&, branch::context::context_entity&); // Switch to Other Branch Context.
    template <typename Fp, typename... Args>
    void execute_to(branch::context::context_entity&, branch::context::context_entity&, execution_argument<Fp, Args...>&);
    //void execute_to(branch::context::context_entity& prev, execution_wrapper              & next); // Execute New Branch Context.
}

    void switch_to (branch::context::context_entity&, branch::context::context_entity&);
    template <typename Fp, typename... Args>
    void execute_to(branch::context::context_entity&, branch::context::context_entity&, execution_argument<Fp, Args...>&);
    //void execute_to(branch::context::context_entity& prev, execution_wrapper              & next);
}
}

template <typename Fp, typename... Args>
void branch::context::internal::execute_to(branch::context::context_entity& prev, branch::context::context_entity& next_ctx, execution_argument<Fp, Args...>& next)
{
    context_store_cpu  (prev.cpu_context)  ;
    context_store_stack(prev.stack_context);

    context_load_stack (next_ctx.stack_context); // RDI : next.stack_context.
    std::apply         (next.exec_function, next.exec_argument);
}

template <typename Fp, typename... Args>
void branch::context::execute_to(branch::context::context_entity& prev, branch::context::context_entity& next_ctx, execution_argument<Fp, Args...>& next)
{
    volatile auto* instack_prev = &prev;
    volatile auto* instack_next = &next_ctx;
    
    internal::execute_to(prev, next_ctx, next);
    context_load_cpu    ((cpu_register&)instack_prev->cpu_context);
}

/*void branch::context::internal::execute_to(branch::context::context_entity& prev, execution_wrapper& next)
{
    context_store_cpu  (prev.cpu_context)  ;
    context_store_stack(prev.stack_context);

    context_load_stack (next.stack_context); // RDI : next.stack_context.
    next       .execute();                   // RDI : next.
}

void branch::context          ::execute_to(branch::context::context_entity& prev, execution_wrapper& next)
{
    volatile context_entity* instack_prev = &prev;
    volatile context_entity* instack_next = &next;
    
    internal::execute_to(prev, next);
    context_load_cpu    ((cpu_register&)instack_prev->cpu_context);
}*/



void branch::context::internal::switch_to(branch::context::context_entity& prev, branch::context::context_entity& next)
{
    context_store_cpu  (prev.cpu_context)  ; // Store Previous CPU Context.
    context_store_stack(prev.stack_context);
    
    context_switch_to  (next);               // Restore Stack Context and Instruction Pointer.
}

void branch::context          ::switch_to(branch::context::context_entity& prev, branch::context::context_entity& next)
{
    volatile context_entity* instack_prev = &prev;
    volatile context_entity* instack_next = &next;
    
    internal::switch_to(prev, next);
    context_load_cpu   ((cpu_register&)instack_prev->cpu_context);
    
}