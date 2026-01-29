.global _check_root_asm
.align 2

_check_root_asm:
    stp x29, x30, [sp, #-16]!
    mov x29, sp

    bl _geteuid

    cmp x0, #0
    b.ne not_root

is_root:
    mov w0, #1
    b exit

not_root:
    mov w0, #0

exit:
    ldp x29, x30, [sp], #16
    ret