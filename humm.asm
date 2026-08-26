bits    64
default rel

extern  ExitProcess
extern  MessageBoxW
global  main

section .data
    msg   db __?utf16?__('我写了个滚木'),0,0
    title db __?utf16?__('标题'),0,0

section .text
main:    
    sub rsp, 40

    xor rcx, rcx
    mov rdx, msg
    mov r8,  title
    xor r9,  r9

    call MessageBoxW

    xor  rcx, rcx
    call ExitProcess
