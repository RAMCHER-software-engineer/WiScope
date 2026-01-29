section .text
global check_root_asm

check_root_asm:
    push rbp
    mov rbp, rsp

    mov rax, 107
    syscall

    cmp rax, 0
    jne not_root

is_root:
    mov rax, 1
    jmp exit

not_root:
    mov rax, 0

exit:
    pop rbp
    ret