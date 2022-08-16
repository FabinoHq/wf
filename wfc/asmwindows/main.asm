;//////////////////////////////////////////////////////////////////////////////;
;/        _______                               ______________________        /;
;/        \\ .   \                     ________/ . . . . . . . . . . /        /;
;/         \\ .   \     ____       ___/   . . .     ________________/         /;
;/          \\ .   \   //   \   __/  . .  _________/ .  .  .  .  /            /;
;/           \\ .   \_//     \_//     ___/    //      __________/             /;
;/            \\ .   \/   _   \/    _/       // .    /___                     /;
;/             \\ .      /\\       /        // .    ____/                     /;
;/              \\ .    /  \\     /       _// .   /                           /;
;/               \\ .  /    \\   /     _//  .    /                            /;
;/                \\__/      \\_/    //_________/                             /;
;/                                                                            /;
;//////////////////////////////////////////////////////////////////////////////;

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
    xor rdx, rdx    ; Clear rdx
    xor r8, r8      ; Clear r8
    xor r9, r9      ; Clear r9
    xor r10, r10    ; Clear r10
    xor r11, r11    ; Clear r11
    xor r12, r12    ; Clear r12

    sub rsp, 40     ; Push stack
    mov r11, rsp    ; Store rsp into r11

    ; Allocate memory
    mov rcx, 67108864       ; 16777216*4 bytes
    call ??_U@YAPEAX_K@Z    ; new[] (size in rcx, return address in rax)
    push rax                ; Push address into stack

    ; Set memory pointer
    mov r12, rax        ; Move address into r12
    add r12, 33554432   ; Add memory offset ((16777216*4)/2 bytes)

    ; Output current rsp value
    mov rcx, rsp
    call WFOutputHex

    ; Output new line
    mov al, 10
    call WFStandardOutput

    xor eax, eax    ; Clear eax  :  Register 
    xor ebx, ebx    ; Clear ebx  :  Back register
    xor ecx, ecx    ; Clear ecx  :  Pointer 
    xor edx, edx    ; Clear edx  :  Back pointer

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

; WFMainEnd : Main program end
WFMainEnd:
    ; Cleanup memory
    pop rcx                     ; Restore address from stack
    call ??_V@YAXPEAX@Z         ; delete[] (address in rcx)

    ; Wait for keyboard input
    call WFKeyboardInput

    ; End of program
    xor rax, rax    ; Clear rax
    add rsp, 40     ; Pop stack
    ret 0           ; Return 0

; WFKeyboardInput : low level keyboard input
WFKeyboardInput:
    push rbx        ; Push rbx
    push rcx        ; Push rcx
    push rdx        ; Push rdx
    push r11        ; Push r11
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
    pop r11         ; Pop r11
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
    push r11        ; Push r11
    push r12        ; Push r12

    xor rcx, rcx    ; Clear rcx
    mov cl, al      ; Move register value into cl
    sub rsp, 40     ; Push stack
    call putchar    ; Output character from cl
    add rsp, 40     ; Pop stack

    pop r12         ; Pop r12
    pop r11         ; Pop r11
    pop rdx         ; Pop rdx
    pop rcx         ; Pop rcx
    pop rbx         ; Pop rbx
    pop rax         ; Pop rax

    ret         ; Return to caller

; output_hex : output hex number (rdx : value to output)
WFOutputHex:
    push rax        ; Push rax
    push rbx        ; Push rbx
    push rcx        ; Push rcx
    push rdx        ; Push rdx
    push r11        ; Push r11
    push r12        ; Push r12

    xor rcx, rcx    ; Clear rcx
    mov cx, 16  ; Loop for 16 digits
    WFOutputHexLoop:

        ; Extract current digit
        mov rax, rdx    ; Move hex value into eax
        shr rax, 60     ; Extract current digit value
        add al, '0'     ; Convert to ASCII value

        cmp al, '9'     ; Compare al with '9'
        jle WFOutputHexDigit ; Jump if less or equal
            add al, ('A'-'9'-1) ; Add ASCII offset for hex digits
        WFOutputHexDigit:

        ; Print current character
        call WFStandardOutput

        ; Next hex digit
        shl rdx, 4   ; Shift edx right by 4bits
    loop WFOutputHexLoop

    pop r12         ; Pop r12
    pop r11         ; Pop r11
    pop rdx         ; Pop rdx
    pop rcx         ; Pop rcx
    pop rbx         ; Pop rbx
    pop rax         ; Pop rax

    ret       ; Return to caller

main endp
_TEXT ENDS
end
