; External functions
EXTRN _kbhit:PROC
EXTRN _getch:PROC
EXTRN _cputs:PROC
EXTRN printf:PROC

; Data segment
.data
    message db "string", 13, 0

; Code segment
.code
main proc

    sub rsp, 40h

    call _kbhit
    call _getch

    mov rcx, offset message
    call printf

    xor eax, eax

    add rsp, 40h
    ret 0

main endp
end
