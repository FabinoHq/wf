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

    ; Read character into al
    call WFKeyboardInput

    ; Output character from al
    call WFStandardOutput

    ; Output new line
    mov al, 10
    call WFStandardOutput

    ; Output string
    mov rbx, OFFSET message     ; Move address of message into rbx
    outputstring:
        mov al, [rbx]           ; Move character into al

        call WFStandardOutput

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
    and rax, 0FFh       ; Mask low byte

    pop r12         ; Pop r12
    pop rdx         ; Pop rdx
    pop rcx         ; Pop rcx
    pop rbx         ; Pop rbx

    ret         ; Return to caller

; WFStandardOutput : low level standard output
WFStandardOutput:
    push rax        ; Push rax
    push rbx        ; Push rbx
    push rcx        ; Push rcx
    push rdx        ; Push rdx
    push r12        ; Push r12

    xor rcx, rcx    ; Clear rcx
    mov cl, al      ; Move register value into cl
    sub rsp, 40     ; Push stack
    call putchar    ; Output character from cl
    add rsp, 40     ; Pop stack

    pop r12         ; Pop r12
    pop rdx         ; Pop rdx
    pop rcx         ; Pop rcx
    pop rbx         ; Pop rbx
    pop rax         ; Pop rax

    ret         ; Return to caller

main endp
_TEXT ENDS
end
