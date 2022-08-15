; External functions
EXTRN _kbhit:PROC       ; _kbhit (Keyboard key press)
EXTRN _getch:PROC       ; _getch (Get last pressed key)
EXTRN putchar:PROC      ; putchar (Output one character to terminal)

EXTRN ??_U@YAPEAX_K@Z:PROC      ; new[]
EXTRN ??_V@YAXPEAX@Z:PROC       ; delete[]

PUBLIC main

; Data segment
.data
    message db "Hello World!", 0

; Code segment
.code
_TEXT SEGMENT
main proc

; WFMain : Main entry point
WFMain:

    ; Program start
    xor rax, rax    ; Clear rax
    xor rbx, rbx    ; Clear rbx
    xor rcx, rcx    ; Clear rcx
    sub rsp, 40     ; Push stack

    ; Allocate memory
    mov ecx, 4096           ; 4096 bytes
    call ??_U@YAPEAX_K@Z    ; new[] (size in ecx, return address in rax)
    push rax                ; Push address into stack

    call WFKeyboardInput

    ; Move character into cl
    mov cl, al

    ; Output character from cl
    sub rsp, 40     ; Push stack
    call putchar
    add rsp, 40     ; Pop stack

    ; Output new line
    mov cl, 10
    sub rsp, 40     ; Push stack
    call putchar
    add rsp, 40     ; Pop stack

    ; Output string
    mov rbx, OFFSET message     ; Move address of message into rbx
    outputstring:
        mov cl, [rbx]           ; Move character into cl

        sub rsp, 40             ; Push stack
        call putchar            ; Output current character
        add rsp, 40             ; Pop stack

        inc rbx                 ; Increment rbx
        mov al, [rbx]           ; Move next character into al
        test al, al             ; Set ZF to 1 if al is equal to 0
        jne outputstring        ; Loop if next character is not 0 (nul)

    ; Cleanup memory
    pop rcx                     ; Restore address from stack
    call ??_V@YAXPEAX@Z         ; delete[] (address in rcx)

    ; End of program
    xor rax, rax    ; Clear rax
    add rsp, 40     ; Pop stack
    ret 0           ; Return 0

main endp

; WFKeyboardInput : low level keyboard input
WFKeyboardInput:

    push rbx        ; Push rbx
    push rcx        ; Push rcx
    push rdx        ; Push rdx
    push r12        ; Push r12

    ; Wait for keyboard input
    inputchar:
        sub rsp, 40         ; Push stack
        call _kbhit         ; Call _kbhit
        add rsp, 40         ; Pop stack
        test eax, eax       ; Set ZF to 1 if eax is equal to 0
        je inputchar        ; Loop if _kbhit returned 0

    ; Get character in al
    xor rax, rax        ; Clear rax
    sub rsp, 40         ; Push stack
    call _getch         ; Call _getch
    add rsp, 40         ; Pop stack

    pop r12         ; Pop r12
    pop rdx         ; Pop rdx
    pop rcx         ; Pop rcx
    pop rbx         ; Pop rbx

    ret         ; Return to caller

_TEXT ENDS
end
