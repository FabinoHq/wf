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

    xor r12, r12        ; Set I/O mode to standard mode
    mov [file_io], 0    ; Set I/O file mode to I/O

    xor eax, eax    ; Clear eax  :  Register 
    xor ebx, ebx    ; Clear ebx  :  Back register
    xor ecx, ecx    ; Clear ecx  :  Pointer 
    xor edx, edx    ; Clear edx  :  Back pointer


    ; Set cursor position
    ;mov eax, 1  ; X cursor position
    ;mov ebx, 2  ; Y cursor position
    ;call WFSetCursorPosition


    ; File I/O
    ; sub rsp, 40     ; Push stack

    ; xor rax, rax                ; Clear rax
    ; mov input_file, rax         ; Clear file handle
    ; lea rdx, file        ; Load file string address
    ; lea r8, file_mode_r  ; Load mode string address
    ; ;lea r8, mode_w      ; Load mode string address
    ; lea rcx, input_file  ; Load file handle address
    ; ; Open file (handle in rcx, path str addr in rdx, mode str addr in r8)
    ; call fopen_s    ; Open file

    ; mov rcx, input_file     ; Move file handle in rcx
    ; test rcx, rcx   ; Check file handle
    ; je filenotfound ; Jump if file is not open

    ; ; Set file cursor position
    ; mov rcx, input_file     ; Move file handle in rcx
    ; xor r8, r8      ; Clear r8 (SEEK_SET)
    ; mov edx, 1      ; Move file cursor position into edx
    ; call fseek      ; Set file cursor position (handle in rcx, position in edx)

    ; ; Read character from file
    ; mov rcx, input_file     ; Move file handle in rcx
    ; call fgetc      ; Read character (handle addr in rcx, character in eax)
    ; mov r15, rax    ; Save character into r15

    ; ; Get file cursor position
    ; mov rcx, input_file     ; Move file handle in rcx
    ; call ftell      ; Get file cursor position (handle in rcx, position in eax)
    ; mov r14, rax    ; Save cursor position into r14

    ; ; Write character to file
    ; ;mov rdx, [rsp]  ; Move file handle in rdx
    ; ;mov rcx, 'a'    ; Move character into rcx
    ; ;call fputc      ; Write character (handle addr in rdx, character in ecx)

    ; ; Close file
    ; mov rcx, input_file     ; Move file handle in rcx
    ; call fclose     ; Close file (handle in rcx)

    ; filenotfound:   ; File not found

    ; add rsp, 40     ; Pop stack


; WFMainEnd : Main program end
WFMainEnd:
    ; Close opened files
    sub rsp, 40             ; Push stack
    mov rax, input_file     ; Load input file handle
    test rax, rax           ; Check input file handle
    je WFMainEndInputFileOk
        ; Close input file
        mov rcx, input_file     ; Move file handle in rcx
        call fclose             ; Close file (handle in rcx)
    WFMainEndInputFileOk:

    mov rax, output_file    ; Load output file handle
    test rax, rax           ; Check output file handle
    je WFMainEndOutputFileOk
        ; Close output file
        mov rcx, output_file    ; Move file handle in rcx
        call fclose             ; Close file (handle in rcx)
    WFMainEndOutputFileOk:

    mov rax, rw_file        ; Load R/W file handle
    test rax, rax           ; Check R/W  file handle
    je WFMainEndFileOk
        ; Close R/W file
        mov rcx, rw_file        ; Move file handle in rcx
        call fclose             ; Close file (handle in rcx)
    WFMainEndFileOk:
    add rsp, 40     ; Pop stack

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
    mov rcx, input_file     ; Load input file handle
    mov rbx, file_io        ; Load file_io mode
    test rbx, rbx           ; Check file_io mode
    je WFStandardInputFileI
        mov rcx, rw_file    ; Load R/W file handle

    WFStandardInputFileI:
    test rcx, rcx           ; Check file handle
    je WFStandardInputEnd   ; No input file

        ; Read character (handle addr in rcx, character in eax)
        call fgetc      ; Call fgetc

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
        mov rdx, output_file    ; Load output file handle
        mov rbx, file_io        ; Load file_io mode
        test rbx, rbx           ; Check file_io mode
        je WFStandardOutputFileO
            mov rdx, rw_file    ; Load R/W file handle

        WFStandardOutputFileO:
        test rdx, rdx           ; Check file handle
        je WFStandardOutputEnd  ; No output file

            ; Write character to file
            movsx rcx, al   ; Move register value into rcx
            ; Write character (handle addr in rdx, character in ecx)
            call fputc      ; Call fputc

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

; WFSetIOMode : Set I/O mode (al : I/O mode, rcx : file path str addr)
WFSetIOMode:
    push rbx        ; Push back register
    push rcx        ; Push pointer
    push rdx        ; Push back pointer
    push r10        ; Push memory address
    push r11        ; Push main esp

    sub rsp, 4000   ; Push stack
    mov r15, r10    ; Store memory address into r15
    movsxd r14, ecx ; Convert pointer into r14
    mov r13, rax    ; Store register into r13

    cmp al, 0       ; Standard I/O mode
    je WFSetIOModeStd           ; Jump to standard I/O mode
    cmp al, 'r'     ; Open input file mode
    je WFSetIOModeOpenInputFile     ; Jump to open input file mode
    cmp al, 'w'     ; Open output file mode
    je WFSetIOModeOpenOutputFile    ; Jump to open output file mode
    cmp al, 'b'     ; Open R/W file mode
    je WFSetIOModeOpenRWFile        ; Jump to open R/W file mode
    cmp al, 'i'     ; Input file I/O mode
    je WFSetIOModeInputFile     ; Jump to file input I/O mode
    cmp al, 'o'     ; Output file I/O mode
    je WFSetIOModeOutputFile    ; Jump to file output I/O mode

    WFSetIOModeStd:             ; Standard I/O mode
        xor r12, r12            ; Set standard I/O mode
        jmp WFSetIOModeEnd

    WFSetIOModeOpenInputFile:   ; Open input file mode
        mov r12, 4              ; Set file input I/O mode
        mov [file_io], 0        ; Set I/O file mode to I/O

        mov rax, input_file     ; Load input file handle
        test rax, rax           ; Check input file handle
        je WFSetIOModeOpenInputFileOk
            ; Close input file
            mov rcx, input_file     ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeOpenInputFileOk:

        mov rax, rw_file        ; Load R/W file handle
        test rax, rax           ; Check R/W file handle
        je WFSetIOModeOpenInputFileRWOk
            ; Close R/W file
            mov rcx, rw_file        ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeOpenInputFileRWOk:

        xor rax, rax                ; Clear rax
        mov input_file, rax         ; Clear input file handle
        mov rw_file, rax            ; Clear R/W file handle

        lea r8, [r15 + r14*4]       ; Load file path memory address into r8
        mov rax, [r8]               ; Move file path into rax
        test rax, rax               ; Check file path
        je WFSetIOModeOpenInputFileErr

        ; Copy 4bytes characters string into 1byte characters string
        sub rsp, 4000               ; Push stack
        mov rbx, rsp                ; Move stack pointer into rbx
        WFSetIOModeOpenInputFileCpy:
            mov r9, [r8]            ; Move character into r9
            mov [rbx], r9           ; Copy character into stack
            add r8, 4               ; Increment paht string pointer
            inc rbx                 ; Increment destination pointer
            test r9, r9             ; Check if character is nul
            jne WFSetIOModeOpenInputFileCpy     ; Copy string loop

        lea rdx, [rsp]              ; Load file string address
        lea r8, file_mode_r         ; Load mode string address
        lea rcx, input_file         ; Load file handle address
        sub rsp, 40                 ; Push stack
        ; Open file (handle in rcx, path str addr in rdx, mode str addr in r8)
        call fopen_s                ; Open file
        add rsp, 4040               ; Pop stack

        mov rcx, input_file         ; Move file handle in rcx
        test rcx, rcx               ; Check file handle
        je WFSetIOModeOpenInputFileErr
            mov r13, 1              ; Set register to 1 (open success)
            jmp WFSetIOModeEnd

        WFSetIOModeOpenInputFileErr:
        xor r13, r13                ; Clear register (open error)
        jmp WFSetIOModeEnd

    WFSetIOModeOpenOutputFile:  ; Open output file mode
        mov r12, 5              ; Set file output I/O mode
        mov [file_io], 0        ; Set I/O file mode to I/O

        mov rax, output_file    ; Load output file handle
        test rax, rax           ; Check output file handle
        je WFSetIOModeOpenOutputFileOk
            ; Close output file
            mov rcx, output_file    ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeOpenOutputFileOk:

        mov rax, rw_file        ; Load R/W file handle
        test rax, rax           ; Check R/W file handle
        je WFSetIOModeOpenOutputFileRWOk
            ; Close R/W file
            mov rcx, rw_file        ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeOpenOutputFileRWOk:

        xor rax, rax                ; Clear rax
        mov output_file, rax        ; Clear output file handle
        mov rw_file, rax            ; Clear R/W file handle

        lea r8, [r15 + r14*4]       ; Load file path memory address into r8
        mov rax, [r8]               ; Move file path into rax
        test rax, rax               ; Check file path
        je WFSetIOModeOpenOutputFileErr

        ; Copy 4bytes characters string into 1byte characters string
        sub rsp, 4000               ; Push stack
        mov rbx, rsp                ; Move stack pointer into rbx
        WFSetIOModeOpenOutputFileCpy:
            mov r9, [r8]            ; Move character into r9
            mov [rbx], r9           ; Copy character into stack
            add r8, 4               ; Increment paht string pointer
            inc rbx                 ; Increment destination pointer
            test r9, r9             ; Check if character is nul
            jne WFSetIOModeOpenOutputFileCpy

        lea rdx, [rsp]              ; Load file string address
        lea r8, file_mode_w         ; Load mode string address
        lea rcx, output_file        ; Load file handle address
        sub rsp, 40                 ; Push stack
        ; Open file (handle in rcx, path str addr in rdx, mode str addr in r8)
        call fopen_s                ; Open file
        add rsp, 4040               ; Pop stack

        mov rcx, output_file        ; Move file handle in rcx
        test rcx, rcx               ; Check file handle
        je WFSetIOModeOpenOutputFileErr
            mov r13, 1              ; Set register to 1 (open success)
            jmp WFSetIOModeEnd

        WFSetIOModeOpenOutputFileErr:
        xor r13, r13                ; Clear register (open error)
        jmp WFSetIOModeEnd

    WFSetIOModeOpenRWFile:      ; Open R/W file mode
        mov r12, 5              ; Set file output I/O mode
        mov [file_io], 1        ; Set I/O file mode to R/W

        mov rax, input_file     ; Load input file handle
        test rax, rax           ; Check input file handle
        je WFSetIOModeRWOpenInputFileOk
            ; Close input file
            mov rcx, input_file     ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeRWOpenInputFileOk:

        mov rax, output_file    ; Load output file handle
        test rax, rax           ; Check output file handle
        je WFSetIOModeRWOpenOutputFileOk
            ; Close output file
            mov rcx, output_file    ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeRWOpenOutputFileOk:

        mov rax, rw_file        ; Load R/W file handle
        test rax, rax           ; Check R/W  file handle
        je WFSetIOModeRWOpenRWFileOk
            ; Close R/W file
            mov rcx, rw_file        ; Move file handle in rcx
            call fclose             ; Close file (handle in rcx)
        WFSetIOModeRWOpenRWFileOk:

        xor rax, rax                ; Clear rax
        mov input_file, rax         ; Clear input file handle
        mov output_file, rax        ; Clear output file handle
        mov rw_file, rax            ; Clear R/W file handle

        lea r8, [r15 + r14*4]       ; Load file path memory address into r8
        mov rax, [r8]               ; Move file path into rax
        test rax, rax               ; Check file path
        je WFSetIOModeRWOpenRWFileErr

        ; Copy 4bytes characters string into 1byte characters string
        sub rsp, 4000               ; Push stack
        mov rbx, rsp                ; Move stack pointer into rbx
        WFSetIOModeOpenRWFileCpy:
            mov r9, [r8]            ; Move character into r9
            mov [rbx], r9           ; Copy character into stack
            add r8, 4               ; Increment paht string pointer
            inc rbx                 ; Increment destination pointer
            test r9, r9             ; Check if character is nul
            jne WFSetIOModeOpenRWFileCpy

        lea rdx, [rsp]              ; Load file string address
        lea r8, file_mode_rw        ; Load mode string address
        lea rcx, rw_file            ; Load file handle address
        sub rsp, 40                 ; Push stack
        ; Open file (handle in rcx, path str addr in rdx, mode str addr in r8)
        call fopen_s                ; Open file
        add rsp, 4040               ; Pop stack

        mov rcx, rw_file            ; Move file handle in rcx
        test rcx, rcx               ; Check file handle
        je WFSetIOModeRWOpenRWFileErr
            mov r13, 1              ; Set register to 1 (open success)
            jmp WFSetIOModeEnd

        WFSetIOModeRWOpenRWFileErr:
        xor r13, r13                ; Clear register (open error)
        jmp WFSetIOModeEnd

    WFSetIOModeInputFile:       ; File input mode
        mov r12, 4              ; Set file input I/O mode
        jmp WFSetIOModeEnd

    WFSetIOModeOutputFile:      ; File output mode
        mov r12, 5              ; Set file output I/O mode
        jmp WFSetIOModeEnd

    WFSetIOModeEnd:
    mov rax, r13    ; Restore register from r13
    add rsp, 4000   ; Pop stack

    pop r11         ; Pop main esp
    pop r10         ; Pop memory address
    pop rdx         ; Pop back pointer
    pop rcx         ; Pop pointer
    pop rbx         ; Pop back register

    ret       ; Return to caller

main endp
_TEXT ENDS
end
