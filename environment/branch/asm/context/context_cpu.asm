; Built in NASM Environment.
; Store / Load CPU Context (Register) of the Function Frame.

global context_store_cpu:function
global context_load_cpu:function

section .text

; void context_store_cpu(branch::context::execution_context&)
; Exported at C Style Mangling.
; By System V Function Convention, RDI Register will be used to store parameter.

context_store_cpu:
    sub rsp              , 0x08
    
    mov qword[rdi]       , rax
    mov qword[rdi + 0x08], rbx
    mov qword[rdi + 0x10], rcx
    mov qword[rdi + 0x18], rdx
                                            ; Stores Stack Instruction Register.
    mov qword[rdi + 0x20], rsi
    mov qword[rdi + 0x28], rdi

    mov qword[rsp]       , rax
    mov rax              , qword[rbp + 0x08] ; Stores RIP Register.

    mov qword[rdi + 0x30], rax
    mov rax              , qword[rsp]

    add rsp              , 0x08
    ret


; void context_load_cpu(branch::context::execution_context&)
; Exported at C Style Mangling.
; By System V Function Convention, RDI Register will be used to store parameter.

context_load_cpu:
; Loads Generic Purposed Register.
    sub rsp, 0x08

    mov rax, qword[rdi]
    mov rbx, qword[rdi + 0x08]
    mov rcx, qword[rdi + 0x10]
    mov rdx, qword[rdi + 0x18]

    mov rsi       , qword[rdi + 0x20]
    mov qword[rsp], rax
    
    mov rax       , rdi
    mov rdi       , qword[rax + 0x28]

    mov rax       , qword[rsp]
    add rsp       , 0x08
    
    ret

