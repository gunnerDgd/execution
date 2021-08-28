global tls_allocate:function
global tls_free:function

section .text

; void tls_allocate(void** global)
tls_allocate:
    sub rsp, 0x08
    