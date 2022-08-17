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

EXTRN __imp_GetStdHandle:PROC               ; Get std handle
EXTRN __imp_SetConsoleCursorPosition:PROC   ; Set cursor position

EXTRN fopen_s:PROC      ; fopen_s (Open file)
EXTRN fclose:PROC       ; fclose (Close file)
EXTRN fgetc:PROC        ; fgetc (Read one character from file)
EXTRN fputc:PROC        ; fputc (Write one character into file)
EXTRN fseek:PROC        ; fseek (Set file cursor position)
EXTRN ftell:PROC        ; ftell (Get file cursor position)

EXTRN ??_U@YAPEAX_K@Z:PROC      ; new[]
EXTRN ??_V@YAXPEAX@Z:PROC       ; delete[]

PUBLIC main

; Data segment
.data
    message db "Hello World!", 00h
    file db "test.txt", 00h

    std_handle dq 00h       ; Std output handle
    input_file dq 00h       ; Input file handle
    output_file dq 00h      ; Output file handle
    rw_file dq 00h          ; R/W file handle
    file_io dq 00h          ; File I/O mode

    file_mode_r db "r", 00h     ; File mode read parameter
    file_mode_w db "w", 00h     ; File mode write parameter
    file_mode_rw db "a+", 00h   ; File mode R/W parameter

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
    xor r13, r13    ; Clear r13
    xor r14, r14    ; Clear r14
    xor r15, r15    ; Clear r15

    sub rsp, 40     ; Push stack

    ; Allocate memory
    mov rcx, 67108864       ; 16777216*4 bytes
    call ??_U@YAPEAX_K@Z    ; new[] (size in rcx, return address in rax)
    push rax                ; Push address into stack

    ; Set memory pointer
    mov r10, rax        ; Move memory address into r10
    add r10, 33554432   ; Add memory offset ((16777216*4)/2 bytes)

    ; Get std output handle
    sub rsp, 40     ; Push stack
    xor rax, rax    ; Clear rax
    mov ecx, -11    ; 0FFFFFFF5H (-11) (STD_OUTPUT_HANDLE)
    call qword ptr __imp_GetStdHandle   ; Get std handle in rax
    add rsp, 40     ; Pop stack
    mov [std_handle], rax   ; Store std handle

    mov r11, rsp    ; Store main rsp into r11

    xor r12, r12    ; Set I/O mode to standard mode

    xor eax, eax    ; Clear eax  :  Register 
    xor ebx, ebx    ; Clear ebx  :  Back register
    xor ecx, ecx    ; Clear ecx  :  Pointer 
    xor edx, edx    ; Clear edx  :  Back pointer

    ; Read character into al
    ;call WFStandardInput

    ; Output character from al
    ;call WFStandardOutput

    ; Output new line
    ;mov al, 10
    ;call WFStandardOutput

    ; Output string
    lea rbx, message    ; Move address of message into rbx
    outputstring:
        mov al, [rbx]           ; Move character into al

        call WFStandardOutput

        inc rbx                 ; Increment rbx
        mov al, [rbx]           ; Move next character into al
        test al, al             ; Set ZF to 1 if al is equal to 0
        jne outputstring        ; Loop if next character is not 0 (nul)


    ; Set cursor position
    ;mov eax, 1  ; X cursor position
    ;mov ebx, 2  ; Y cursor position
    ;call WFSetCursorPosition


    ; File I/O
    sub rsp, 40     ; Push stack

    xor rax, rax                ; Clear rax
    mov input_file, rax         ; Clear file handle
    lea rdx, offset file        ; Load file string address
    lea r8, offset file_mode_r  ; Load mode string address
    ;lea r8, offset mode_w      ; Load mode string address
    lea rcx, input_file  ; Load file handle address
    ; Open file (handle in rcx, path str addr in rdx, mode str addr in r8)
    call fopen_s    ; Open file

    mov rcx, input_file     ; Move file handle in rcx
    test rcx, rcx   ; Check file handle
    je filenotfound ; Jump if file is not open

    ; Set file cursor position
    mov rcx, input_file     ; Move file handle in rcx
    xor r8, r8      ; Clear r8 (SEEK_SET)
    mov edx, 1      ; Move file cursor position into edx
    call fseek      ; Set file cursor position (handle in rcx, position in edx)

    ; Read character from file
    mov rcx, input_file     ; Move file handle in rcx
    call fgetc      ; Read character (handle addr in rcx, character in eax)
    mov r15, rax    ; Save character into r15

    ; Get file cursor position
    mov rcx, input_file     ; Move file handle in rcx
    call ftell      ; Get file cursor position (handle in rcx, position in eax)
    mov r14, rax    ; Save cursor position into r14

    ; Write character to file
    ;mov rdx, [rsp]  ; Move file handle in rdx
    ;mov rcx, 'a'    ; Move character into rcx
    ;call fputc      ; Write character (handle addr in rdx, character in ecx)

    ; Close file
    mov rcx, input_file     ; Move file handle in rcx
    call fclose     ; Close file (handle in rcx)

    filenotfound:   ; File not found

    add rsp, 40     ; Pop stack


    ; Output new line
    mov al, 10
    call WFStandardOutput

    ; Output character
    mov rax, r15    ; Restore character from r15
    call WFStandardOutput

    ; Output new line
    mov al, 10
    call WFStandardOutput

    ; Output file cursor position
    mov rdx, r14
    call WFOutputHex


; WFMainEnd : Main program end
WFMainEnd:
    ; Cleanup memory
    pop rcx                     ; Restore address from stack
    call ??_V@YAXPEAX@Z         ; delete[] (address in rcx)

    ; Wait for keyboard input
    xor r12, r12    ; Set I/O mode to standard mode
    call WFStandardInput

    ; End of program
    xor rax, rax    ; Clear rax
    add rsp, 40     ; Pop stack
    ret 0           ; Return 0

; WFStandardInput : low level standard input
WFStandardInput:
    push rbx        ; Push back register
    push rcx        ; Push pointer
    push rdx        ; Push back pointer
    push r10        ; Push memory address
    push r11        ; Push main esp
    push r12        ; Push iomode

    sub rsp, 40     ; Push stack

    cmp r12, 0      ; Standard I/O mode
    je WFStandardInputStd      ; Jump to standard input mode
    cmp r12, 4      ; Input file I/O mode
    je WFStandardInputFile     ; Jump to file input mode
    cmp r12, 5      ; Output file I/O mode
    je WFStandardInputEnd      ; No input

    WFStandardInputStd:     ; Standard input mode

        ; Wait for keyboard input
        WFStandardInputChar:
            call _kbhit         ; Call _kbhit
            test eax, eax       ; Set ZF to 1 if eax is equal to 0
            je WFStandardInputChar      ; Loop if _kbhit returned 0

        ; Get character in al
        xor rax, rax        ; Clear rax
        call _getch         ; Call _getch
        and rax, 0FFh       ; Mask low byte

        jmp WFStandardInputEnd

    WFStandardInputFile:    ; File input mode
        jmp WFStandardInputEnd

    WFStandardInputEnd:

    add rsp, 40     ; Pop stack

    pop r12         ; Pop iomode
    pop r11         ; Pop main esp
    pop r10         ; Pop memory address
    pop rdx         ; Pop back pointer
    pop rcx         ; Pop pointer
    pop rbx         ; Pop back register

    ret         ; Return to caller

; WFStandardOutput : low level standard output
WFStandardOutput:
    push rax        ; Push register
    push rbx        ; Push back register
    push rcx        ; Push pointer
    push rdx        ; Push back pointer
    push r10        ; Push memory address
    push r11        ; Push main esp
    push r12        ; Push iomode

    sub rsp, 40     ; Push stack

    cmp r12, 0      ; Standard I/O mode
    je WFStandardOutputStd      ; Jump to standard output mode
    cmp r12, 4      ; Input file I/O mode
    je WFStandardOutputEnd      ; No output
    cmp r12, 5      ; Output file I/O mode
    je WFStandardOutputFile     ; Jump to file output mode

    WFStandardOutputStd:    ; Standard output mode
        xor rcx, rcx    ; Clear rcx
        mov cl, al      ; Move register value into cl
        call putchar    ; Output character from cl
        jmp WFStandardOutputEnd

    WFStandardOutputFile:   ; File output mode
        jmp WFStandardOutputEnd

    WFStandardOutputEnd:

    add rsp, 40     ; Pop stack
    pop r12         ; Pop iomode
    pop r11         ; Pop main esp
    pop r10         ; Pop memory address
    pop rdx         ; Pop back pointer
    pop rcx         ; Pop pointer
    pop rbx         ; Pop back register
    pop rax         ; Pop register

    ret         ; Return to caller

; WFSetCursorPosition : Set terminal cursor position (x in ax, y in bx)
WFSetCursorPosition:
    push rax        ; Push register
    push rbx        ; Push back register
    push rcx        ; Push pointer
    push rdx        ; Push back pointer
    push r10        ; Push memory address
    push r11        ; Push main esp
    push r12        ; Push iomode

    sub rsp, 40     ; Push stack

    cmp r12, 0      ; Standard I/O mode
    je WFSetCursorStd           ; Jump to standard output mode
    cmp r12, 4      ; Input file I/O mode
    je WFSetCursorInputFile     ; Jump to file input mode
    cmp r12, 5      ; Output file I/O mode
    je WFSetCursorOutputFile    ; Jump to file output mode

    WFSetCursorStd:     ; Standard I/O mode
        xor rdx, rdx    ; Clear rdx
        mov dx, bx      ; Y cursor position
        shl edx, 16     ; Shift Y position to high
        mov dx, ax      ; X cursor position

        ; Set cursor position
        mov rcx, std_handle     ; Move handle in rcx
        ; Std handle in rcx, Coords in edx(X : low 4bytes, Y : high 4bytes)
        call qword ptr __imp_SetConsoleCursorPosition

        jmp WFSetCursorEnd

    WFSetCursorInputFile:   ; File input mode
        jmp WFSetCursorEnd

    WFSetCursorOutputFile:  ; File output mode
        jmp WFSetCursorEnd

    WFSetCursorEnd:

    add rsp, 40     ; Pop stack

    pop r12         ; Pop iomode
    pop r11         ; Pop main esp
    pop r10         ; Pop memory address
    pop rdx         ; Pop back pointer
    pop rcx         ; Pop pointer
    pop rbx         ; Pop back register
    pop rax         ; Pop register

    ret       ; Return to caller

; WFOutputHex : output hex number (rdx : value to output)
WFOutputHex:
    push rax        ; Push register
    push rbx        ; Push back register
    push rcx        ; Push pointer
    push rdx        ; Push back pointer
    push r10        ; Push memory address
    push r11        ; Push main esp
    push r12        ; Push iomode

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

    pop r12         ; Pop iomode
    pop r11         ; Pop main esp
    pop r10         ; Pop memory address
    pop rdx         ; Pop back pointer
    pop rcx         ; Pop pointer
    pop rbx         ; Pop back register
    pop rax         ; Pop register

    ret       ; Return to caller

main endp
_TEXT ENDS
end
