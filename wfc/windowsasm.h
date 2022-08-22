////////////////////////////////////////////////////////////////////////////////
//        _______                               ______________________        //
//        \\ .   \                     ________/ . . . . . . . . . . /        //
//         \\ .   \     ____       ___/   . . .     ________________/         //
//          \\ .   \   //   \   __/  . .  _________/ .  .  .  .  /            //
//           \\ .   \_//     \_//     ___/    //      __________/             //
//            \\ .   \/   _   \/    _/       // .    /___                     //
//             \\ .      /\\       /        // .    ____/                     //
//              \\ .    /  \\     /       _// .   /                           //
//               \\ .  /    \\   /     _//  .    /                            //
//                \\__/      \\_/    //_________/                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//   This is free and unencumbered software released into the public domain.  //
//                                                                            //
//   Anyone is free to copy, modify, publish, use, compile, sell, or          //
//   distribute this software, either in source code form or as a compiled    //
//   binary, for any purpose, commercial or non-commercial, and by any        //
//   means.                                                                   //
//                                                                            //
//   In jurisdictions that recognize copyright laws, the author or authors    //
//   of this software dedicate any and all copyright interest in the          //
//   software to the public domain. We make this dedication for the benefit   //
//   of the public at large and to the detriment of our heirs and             //
//   successors. We intend this dedication to be an overt act of              //
//   relinquishment in perpetuity of all present and future rights to this    //
//   software under copyright law.                                            //
//                                                                            //
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          //
//   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       //
//   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   //
//   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR        //
//   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,    //
//   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    //
//   OTHER DEALINGS IN THE SOFTWARE.                                          //
//                                                                            //
//   For more information, please refer to <https://unlicense.org>            //
////////////////////////////////////////////////////////////////////////////////
//    WFC : WF Compiler                                                       //
//     windowsasm.h : WFC Windows assembly                                    //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFC_WINDOWSASM_HEADER
#define WFC_WINDOWSASM_HEADER


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly header                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMHeader[] =
        ";///////////////////////////////////////"
        "///////////////////////////////////////;\n"
        ";/        _______                       "
        "        ______________________        /;\n"
        ";/        \\\\ .   \\                     _"
        "_______/ . . . . . . . . . . /        /;\n"
        ";/         \\\\ .   \\     ____       ___/ "
        "  . . .     ________________/         /;\n"
        ";/          \\\\ .   \\   //   \\   __/  . ."
        "  _________/ .  .  .  .  /            /;\n"
        ";/           \\\\ .   \\_//     \\_//     __"
        "_/    //      __________/             /;\n"
        ";/            \\\\ .   \\/   _   \\/    _/  "
        "     // .    /___                     /;\n"
        ";/             \\\\ .      /\\\\       /    "
        "    // .    ____/                     /;\n"
        ";/              \\\\ .    /  \\\\     /     "
        "  _// .   /                           /;\n"
        ";/               \\\\ .  /    \\\\   /     _"
        "//  .    /                            /;\n"
        ";/                \\\\__/      \\\\_/    //_"
        "________/                             /;\n"
        ";/                                      "
        "                                      /;\n"
        ";///////////////////////////////////////"
        "///////////////////////////////////////;\n"
        ";/  Assembly compiled by WFC (WF Compile"
        "r)                                    /;\n"
        ";///////////////////////////////////////"
        "///////////////////////////////////////;\n"
        "\n"
        "; External functions\n"
        "EXTRN _kbhit:PROC       ; _kbhit (Keyboard key press)\n"
        "EXTRN _getch:PROC       ; _getch (Get last pressed key)\n"
        "EXTRN putchar:PROC      ; putchar (Output one character to terminal)\n"
        "\n"
        "EXTRN __imp_GetStdHandle:PROC               ; Get std handle\n"
        "EXTRN __imp_SetConsoleCursorPosition:PROC   ; Set cursor position\n"
        "\n"
        "EXTRN fopen_s:PROC      ; fopen_s (Open file)\n"
        "EXTRN fclose:PROC       ; fclose (Close file)\n"
        "EXTRN fgetc:PROC        ; fgetc (Read one character from file)\n"
        "EXTRN fputc:PROC        ; fputc (Write one character into file)\n"
        "EXTRN fseek:PROC        ; fseek (Set file cursor position)\n"
        "EXTRN ftell:PROC        ; ftell (Get file cursor position)\n"
        "\n"
        "EXTRN ??_U@YAPEAX_K@Z:PROC      ; new[]\n"
        "EXTRN ??_V@YAXPEAX@Z:PROC       ; delete[]\n"
        "\n"
        "PUBLIC main\n"
        "\n"
        "; Data segment\n"
        ".data\n"
        "    std_handle dq 00h       ; Std output handle\n"
        "    input_file dq 00h       ; Input file handle\n"
        "    output_file dq 00h      ; Output file handle\n"
        "    rw_file dq 00h          ; R/W file handle\n"
        "    file_io dq 00h          ; File I/O mode\n"
        "\n"
        "    file_mode_r db \"r\", 00h     ; File mode read parameter\n"
        "    file_mode_w db \"w\", 00h     ; File mode write parameter\n"
        "    file_mode_rw db \"a+\", 00h   ; File mode R/W parameter\n"
        "\n"
        "; Code segment\n"
        ".code\n"
        "_TEXT SEGMENT\n"
        "main proc\n"
        "\n"
        "; WFMain : Main entry point\n"
        "WFMain:\n"
        "\n"
        "    ; Program start\n"
        "    xor rax, rax    ; Clear rax\n"
        "    xor rbx, rbx    ; Clear rbx\n"
        "    xor rcx, rcx    ; Clear rcx\n"
        "    xor rdx, rdx    ; Clear rdx\n"
        "    xor r8, r8      ; Clear r8\n"
        "    xor r9, r9      ; Clear r9\n"
        "    xor r10, r10    ; Clear r10\n"
        "    xor r11, r11    ; Clear r11\n"
        "    xor r12, r12    ; Clear r12\n"
        "    xor r13, r13    ; Clear r13\n"
        "    xor r14, r14    ; Clear r14\n"
        "    xor r15, r15    ; Clear r15\n"
        "\n"
        "    sub rsp, 32     ; Push stack (16 bytes boundary)\n"
        "\n"
        "    ; Allocate memory\n"
        "    mov rcx, 67108864       ; 16777216*4 bytes\n"
        "    call ??_U@YAPEAX_K@Z    ; new[] "
        "(size in rcx, return address in rax)\n"
        "    push rax                ; Push address into stack\n"
        "\n"
        "    ; Set memory pointer\n"
        "    mov r10, rax        ; Move memory address into r10\n"
        "    add r10, 33554432   ; Add memory offset ((16777216*4)/2 bytes)\n"
        "\n"
        "    ; Get std output handle\n"
        "    sub rsp, 32     ; Push stack\n"
        "    xor rax, rax    ; Clear rax\n"
        "    mov ecx, -11    ; 0FFFFFFF5H (-11) (STD_OUTPUT_HANDLE)\n"
        "    call qword ptr __imp_GetStdHandle   ; Get std handle in rax\n"
        "    add rsp, 32     ; Pop stack\n"
        "    mov [std_handle], rax   ; Store std handle\n"
        "\n"
        "    mov r11, rsp    ; Store main rsp into r11\n"
        "\n"
        "    xor r12, r12        ; Set I/O mode to standard mode\n"
        "    mov [file_io], 0    ; Set I/O file mode to I/O\n"
        "\n"
        "    xor eax, eax    ; Clear eax  :  Register \n"
        "    xor ebx, ebx    ; Clear ebx  :  Back register\n"
        "    xor ecx, ecx    ; Clear ecx  :  Pointer \n"
        "    xor edx, edx    ; Clear edx  :  Back pointer\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly footer                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMFooter[] =
        "\n"
        "; WFMainEnd : Main program end\n"
        "WFMainEnd:\n"
        "    ; Close opened files\n"
        "    sub rsp, 32             ; Push stack\n"
        "    mov rax, input_file     ; Load input file handle\n"
        "    test rax, rax           ; Check input file handle\n"
        "    je WFMainEndInputFileOk\n"
        "        ; Close input file\n"
        "        mov rcx, input_file     ; Move file handle in rcx\n"
        "        call fclose             ; Close file (handle in rcx)\n"
        "    WFMainEndInputFileOk:\n"
        "\n"
        "    mov rax, output_file    ; Load output file handle\n"
        "    test rax, rax           ; Check output file handle\n"
        "    je WFMainEndOutputFileOk\n"
        "        ; Close output file\n"
        "        mov rcx, output_file    ; Move file handle in rcx\n"
        "        call fclose             ; Close file (handle in rcx)\n"
        "    WFMainEndOutputFileOk:\n"
        "\n"
        "    mov rax, rw_file        ; Load R/W file handle\n"
        "    test rax, rax           ; Check R/W  file handle\n"
        "    je WFMainEndFileOk\n"
        "        ; Close R/W file\n"
        "        mov rcx, rw_file        ; Move file handle in rcx\n"
        "        call fclose             ; Close file (handle in rcx)\n"
        "    WFMainEndFileOk:\n"
        "    add rsp, 32     ; Pop stack\n"
        "\n"
        "    ; Cleanup memory\n"
        "    pop rcx                     ; Restore address from stack\n"
        "    call ??_V@YAXPEAX@Z         ; delete[] (address in rcx)\n"
        "\n"
        "    ; Wait for keyboard input\n"
        "    xor r12, r12    ; Set I/O mode to standard mode\n"
        "    call WFStandardInput\n"
        "\n"
        "    ; End of program\n"
        "    xor rax, rax    ; Clear rax\n"
        "    add rsp, 32     ; Pop stack (16 bytes boundary)\n"
        "    ret 0           ; Return 0\n"
        "\n"
        "; WFStandardInput : low level standard input\n"
        "WFStandardInput:\n"
        "    push rbx        ; Push back register\n"
        "    push rcx        ; Push pointer\n"
        "    push rdx        ; Push back pointer\n"
        "    push r10        ; Push memory address\n"
        "    push r11        ; Push main esp\n"
        "    push r12        ; Push iomode\n"
        "\n"
        "    sub rsp, 40     ; Push stack (16 bytes boundary)\n"
        "\n"
        "    cmp r12, 0      ; Standard I/O mode\n"
        "    je WFStandardInputStd      ; Jump to standard input mode\n"
        "    cmp r12, 4      ; Input file I/O mode\n"
        "    je WFStandardInputFile     ; Jump to file input mode\n"
        "    cmp r12, 5      ; Output file I/O mode\n"
        "    je WFStandardInputEnd      ; No input\n"
        "\n"
        "    WFStandardInputStd:     ; Standard input mode\n"
        "\n"
        "        ; Wait for keyboard input\n"
        "        WFStandardInputChar:\n"
        "            call _kbhit         ; Call _kbhit\n"
        "            test eax, eax       ; Set ZF to 1 if eax is equal to 0\n"
        "            je WFStandardInputChar      ; Loop if _kbhit returned 0\n"
        "\n"
        "        ; Get character in al\n"
        "        xor rax, rax        ; Clear rax\n"
        "        call _getch         ; Call _getch\n"
        "        and rax, 0FFh       ; Mask low byte\n"
        "\n"
        "        jmp WFStandardInputEnd\n"
        "\n"
        "    WFStandardInputFile:    ; File input mode\n"
        "    mov rcx, input_file     ; Load input file handle\n"
        "    mov rbx, file_io        ; Load file_io mode\n"
        "    test rbx, rbx           ; Check file_io mode\n"
        "    je WFStandardInputFileI\n"
        "        mov rcx, rw_file    ; Load R/W file handle\n"
        "\n"
        "    WFStandardInputFileI:\n"
        "    test rcx, rcx           ; Check file handle\n"
        "    je WFStandardInputEnd   ; No input file\n"
        "\n"
        "        ; Read character (handle addr in rcx, character in eax)\n"
        "        call fgetc      ; Call fgetc\n"
        "\n"
        "    WFStandardInputEnd:\n"
        "    add rsp, 40     ; Pop stack (16 bytes boundary)\n"
        "\n"
        "    pop r12         ; Pop iomode\n"
        "    pop r11         ; Pop main esp\n"
        "    pop r10         ; Pop memory address\n"
        "    pop rdx         ; Pop back pointer\n"
        "    pop rcx         ; Pop pointer\n"
        "    pop rbx         ; Pop back register\n"
        "\n"
        "    ret         ; Return to caller\n"
        "\n"
        "; WFStandardOutput : low level standard output\n"
        "WFStandardOutput:\n"
        "    push rax        ; Push register\n"
        "    push rbx        ; Push back register\n"
        "    push rcx        ; Push pointer\n"
        "    push rdx        ; Push back pointer\n"
        "    push r10        ; Push memory address\n"
        "    push r11        ; Push main esp\n"
        "    push r12        ; Push iomode\n"
        "\n"
        "    sub rsp, 32     ; Push stack (16 bytes boundary)\n"
        "\n"
        "    cmp r12, 0      ; Standard I/O mode\n"
        "    je WFStandardOutputStd      ; Jump to standard output mode\n"
        "    cmp r12, 4      ; Input file I/O mode\n"
        "    je WFStandardOutputEnd      ; No output\n"
        "    cmp r12, 5      ; Output file I/O mode\n"
        "    je WFStandardOutputFile     ; Jump to file output mode\n"
        "\n"
        "    WFStandardOutputStd:    ; Standard output mode\n"
        "        xor rcx, rcx    ; Clear rcx\n"
        "        mov cl, al      ; Move register value into cl\n"
        "        call putchar    ; Output character from cl\n"
        "        jmp WFStandardOutputEnd\n"
        "\n"
        "    WFStandardOutputFile:   ; File output mode\n"
        "        mov rdx, output_file    ; Load output file handle\n"
        "        mov rbx, file_io        ; Load file_io mode\n"
        "        test rbx, rbx           ; Check file_io mode\n"
        "        je WFStandardOutputFileO\n"
        "            mov rdx, rw_file    ; Load R/W file handle\n"
        "\n"
        "        WFStandardOutputFileO:\n"
        "        test rdx, rdx           ; Check file handle\n"
        "        je WFStandardOutputEnd  ; No output file\n"
        "\n"
        "            ; Write character to file\n"
        "            movsx rcx, al   ; Move register value into rcx\n"
        "            ; Write character (handle addr in rdx, character in ecx)\n"
        "            call fputc      ; Call fputc\n"
        "\n"
        "    WFStandardOutputEnd:\n"
        "    add rsp, 32     ; Pop stack (16 bytes boundary)\n"
        "\n"
        "    pop r12         ; Pop iomode\n"
        "    pop r11         ; Pop main esp\n"
        "    pop r10         ; Pop memory address\n"
        "    pop rdx         ; Pop back pointer\n"
        "    pop rcx         ; Pop pointer\n"
        "    pop rbx         ; Pop back register\n"
        "    pop rax         ; Pop register\n"
        "\n"
        "    ret         ; Return to caller\n"
        "\n"
        "; WFSetCursorPosition : Set terminal "
        "cursor position (x in ax, y in bx)\n"
        "WFSetCursorPosition:\n"
        "    push rax        ; Push register\n"
        "    push rbx        ; Push back register\n"
        "    push rcx        ; Push pointer\n"
        "    push rdx        ; Push back pointer\n"
        "    push r10        ; Push memory address\n"
        "    push r11        ; Push main esp\n"
        "    push r12        ; Push iomode\n"
        "\n"
        "    sub rsp, 32     ; Push stack  (16 bytes boundary)\n"
        "\n"
        "    cmp r12, 0      ; Standard I/O mode\n"
        "    je WFSetCursorStd           ; Jump to standard output mode\n"
        "    cmp r12, 4      ; Input file I/O mode\n"
        "    je WFSetCursorInputFile     ; Jump to file input mode\n"
        "    cmp r12, 5      ; Output file I/O mode\n"
        "    je WFSetCursorOutputFile    ; Jump to file output mode\n"
        "\n"
        "    WFSetCursorStd:     ; Standard I/O mode\n"
        "        xor rdx, rdx    ; Clear rdx\n"
        "        mov dx, bx      ; Y cursor position\n"
        "        shl edx, 16     ; Shift Y position to high\n"
        "        mov dx, ax      ; X cursor position\n"
        "\n"
        "        ; Set cursor position\n"
        "        mov rcx, std_handle     ; Move handle in rcx\n"
        "        ; Std handle in rcx, Coords in edx"
        "(X : low 4bytes, Y : high 4bytes)\n"
        "        call qword ptr __imp_SetConsoleCursorPosition\n"
        "\n"
        "        jmp WFSetCursorEnd\n"
        "\n"
        "    WFSetCursorInputFile:   ; File input mode\n"
        "        mov rcx, input_file     ; Move file handle in rcx\n"
        "        mov rbx, file_io        ; Load file_io mode\n"
        "        test rbx, rbx           ; Check file_io mode\n"
        "        je WFSetCursorInputFileI\n"
        "            mov rcx, rw_file    ; Load R/W file handle\n"
        "\n"
        "        WFSetCursorInputFileI:\n"
        "        xor r8, r8              ; Clear r8 (SEEK_SET)\n"
        "        mov edx, eax            ; Move file cursor position into edx\n"
        "        ; Set file cursor position (handle in rcx, position in edx)\n"
        "        call fseek              ; Call fseek\n"
        "        jmp WFSetCursorEnd\n"
        "\n"
        "    WFSetCursorOutputFile:  ; File output mode\n"
        "        mov rcx, output_file    ; Load output file handle\n"
        "        mov rbx, file_io        ; Load file_io mode\n"
        "        test rbx, rbx           ; Check file_io mode\n"
        "        je WFSetCursorOutputFileO\n"
        "            mov rcx, rw_file    ; Load R/W file handle\n"
        "\n"
        "        WFSetCursorOutputFileO:\n"
        "        xor r8, r8              ; Clear r8 (SEEK_SET)\n"
        "        mov edx, eax            ; Move file cursor position into edx\n"
        "        ; Set file cursor position (handle in rcx, position in edx)\n"
        "        call fseek              ; Call fseek\n"
        "        jmp WFSetCursorEnd\n"
        "\n"
        "    WFSetCursorEnd:\n"
        "    add rsp, 32     ; Pop stack  (16 bytes boundary)\n"
        "\n"
        "    pop r12         ; Pop iomode\n"
        "    pop r11         ; Pop main esp\n"
        "    pop r10         ; Pop memory address\n"
        "    pop rdx         ; Pop back pointer\n"
        "    pop rcx         ; Pop pointer\n"
        "    pop rbx         ; Pop back register\n"
        "    pop rax         ; Pop register\n"
        "\n"
        "    ret       ; Return to caller\n"
        "\n"
        "; WFSetIOMode : Set I/O mode "
        "(al : I/O mode, rcx : file path str addr)\n"
        "WFSetIOMode:\n"
        "    push rbx        ; Push back register\n"
        "    push rcx        ; Push pointer\n"
        "    push rdx        ; Push back pointer\n"
        "    push r10        ; Push memory address\n"
        "    push r11        ; Push main esp\n"
        "\n"
        "    sub rsp, 48     ; Push stack (16 bytes boundary)\n"
        "    mov r15, r10    ; Store memory address into r15\n"
        "    movsxd r14, ecx ; Convert pointer into r14\n"
        "    mov r13, rax    ; Store register into r13\n"
        "\n"
        "    cmp al, 0       ; Standard I/O mode\n"
        "    je WFSetIOModeStd           ; Jump to standard I/O mode\n"
        "    cmp al, 'r'     ; Open input file mode\n"
        "    je WFSetIOModeOpenInputFile     ; Jump to open input file mode\n"
        "    cmp al, 'w'     ; Open output file mode\n"
        "    je WFSetIOModeOpenOutputFile    ; Jump to open output file mode\n"
        "    cmp al, 'b'     ; Open R/W file mode\n"
        "    je WFSetIOModeOpenRWFile        ; Jump to open R/W file mode\n"
        "    cmp al, 'i'     ; Input file I/O mode\n"
        "    je WFSetIOModeInputFile     ; Jump to file input I/O mode\n"
        "    cmp al, 'o'     ; Output file I/O mode\n"
        "    je WFSetIOModeOutputFile    ; Jump to file output I/O mode\n"
        "\n"
        "    WFSetIOModeStd:             ; Standard I/O mode\n"
        "        xor r12, r12            ; Set standard I/O mode\n"
        "        jmp WFSetIOModeEnd\n"
        "\n"
        "    WFSetIOModeOpenInputFile:   ; Open input file mode\n"
        "        mov r12, 4              ; Set file input I/O mode\n"
        "        mov [file_io], 0        ; Set I/O file mode to I/O\n"
        "\n"
        "        mov rax, input_file     ; Load input file handle\n"
        "        test rax, rax           ; Check input file handle\n"
        "        je WFSetIOModeOpenInputFileOk\n"
        "            ; Close input file\n"
        "            mov rcx, input_file     ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeOpenInputFileOk:\n"
        "\n"
        "        mov rax, rw_file        ; Load R/W file handle\n"
        "        test rax, rax           ; Check R/W file handle\n"
        "        je WFSetIOModeOpenInputFileRWOk\n"
        "            ; Close R/W file\n"
        "            mov rcx, rw_file        ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeOpenInputFileRWOk:\n"
        "\n"
        "        xor rax, rax                ; Clear rax\n"
        "        mov input_file, rax         ; Clear input file handle\n"
        "        mov rw_file, rax            ; Clear R/W file handle\n"
        "\n"
        "        lea r8, [r15 + r14*4]       "
        "; Load file path memory address into r8\n"
        "        mov rax, [r8]               ; Move file path into rax\n"
        "        test rax, rax               ; Check file path\n"
        "        je WFSetIOModeOpenInputFileErr\n"
        "\n"
        "        ; Copy 4bytes characters string into 1byte characters string\n"
        "        sub rsp, 4096               ; Push stack\n"
        "        mov rbx, rsp                ; Move stack pointer into rbx\n"
        "        mov rcx, 4000               ; Loop for 4000 characters max\n"
        "        WFSetIOModeOpenInputFileCpy:\n"
        "            mov r9, [r8]            ; Move character into r9\n"
        "            mov [rbx], r9           ; Copy character into stack\n"
        "            add r8, 4               ; Increment paht string pointer\n"
        "            inc rbx                 ; Increment destination pointer\n"
        "            test r9, r9             ; Check if character is nul\n"
        "            je WFSetIOModeOpenInputFileDone     ; Copy string done\n"
        "            loop WFSetIOModeOpenInputFileCpy    ; Copy string loop\n"
        "        WFSetIOModeOpenInputFileDone:\n"
        "        xor r9, r9                  ; Clear r9\n"
        "        mov [rbx], r9               ; Add nul character\n"
        "\n"
        "        lea rdx, [rsp]              ; Load file string address\n"
        "        lea r8, file_mode_r         ; Load mode string address\n"
        "        lea rcx, input_file         ; Load file handle address\n"
        "        sub rsp, 32                 ; Push stack\n"
        "        ; Open file (handle in rcx, "
        "path str addr in rdx, mode str addr in r8)\n"
        "        call fopen_s                ; Open file\n"
        "        add rsp, 4128               ; Pop stack\n"
        "\n"
        "        mov rcx, input_file         ; Move file handle in rcx\n"
        "        test rcx, rcx               ; Check file handle\n"
        "        je WFSetIOModeOpenInputFileErr\n"
        "            mov r13, 1              "
        "; Set register to 1 (open success)\n"
        "            jmp WFSetIOModeEnd\n"
        "\n"
        "        WFSetIOModeOpenInputFileErr:\n"
        "        xor r13, r13                ; Clear register (open error)\n"
        "        jmp WFSetIOModeEnd\n"
        "\n"
        "    WFSetIOModeOpenOutputFile:  ; Open output file mode\n"
        "        mov r12, 5              ; Set file output I/O mode\n"
        "        mov [file_io], 0        ; Set I/O file mode to I/O\n"
        "\n"
        "        mov rax, output_file    ; Load output file handle\n"
        "        test rax, rax           ; Check output file handle\n"
        "        je WFSetIOModeOpenOutputFileOk\n"
        "            ; Close output file\n"
        "            mov rcx, output_file    ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeOpenOutputFileOk:\n"
        "\n"
        "        mov rax, rw_file        ; Load R/W file handle\n"
        "        test rax, rax           ; Check R/W file handle\n"
        "        je WFSetIOModeOpenOutputFileRWOk\n"
        "            ; Close R/W file\n"
        "            mov rcx, rw_file        ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeOpenOutputFileRWOk:\n"
        "\n"
        "        xor rax, rax                ; Clear rax\n"
        "        mov output_file, rax        ; Clear output file handle\n"
        "        mov rw_file, rax            ; Clear R/W file handle\n"
        "\n"
        "        lea r8, [r15 + r14*4]       "
        "; Load file path memory address into r8\n"
        "        mov rax, [r8]               ; Move file path into rax\n"
        "        test rax, rax               ; Check file path\n"
        "        je WFSetIOModeOpenOutputFileErr\n"
        "\n"
        "        ; Copy 4bytes characters string into 1byte characters string\n"
        "        sub rsp, 4096               ; Push stack\n"
        "        mov rbx, rsp                ; Move stack pointer into rbx\n"
        "        mov rcx, 4000               ; Loop for 4000 characters max\n"
        "        WFSetIOModeOpenOutputFileCpy:\n"
        "            mov r9, [r8]            ; Move character into r9\n"
        "            mov [rbx], r9           ; Copy character into stack\n"
        "            add r8, 4               ; Increment paht string pointer\n"
        "            inc rbx                 ; Increment destination pointer\n"
        "            test r9, r9             ; Check if character is nul\n"
        "            je WFSetIOModeOpenOutputFileDone    ; Copy string done\n"
        "            loop WFSetIOModeOpenOutputFileCpy   ; Copy string loop\n"
        "        WFSetIOModeOpenOutputFileDone:\n"
        "        xor r9, r9                  ; Clear r9\n"
        "        mov [rbx], r9               ; Add nul character\n"
        "\n"
        "        lea rdx, [rsp]              ; Load file string address\n"
        "        lea r8, file_mode_w         ; Load mode string address\n"
        "        lea rcx, output_file        ; Load file handle address\n"
        "        sub rsp, 32                 ; Push stack\n"
        "        ; Open file (handle in rcx, "
        "path str addr in rdx, mode str addr in r8)\n"
        "        call fopen_s                ; Open file\n"
        "        add rsp, 4128               ; Pop stack\n"
        "\n"
        "        mov rcx, output_file        ; Move file handle in rcx\n"
        "        test rcx, rcx               ; Check file handle\n"
        "        je WFSetIOModeOpenOutputFileErr\n"
        "            mov r13, 1              "
        "; Set register to 1 (open success)\n"
        "            jmp WFSetIOModeEnd\n"
        "\n"
        "        WFSetIOModeOpenOutputFileErr:\n"
        "        xor r13, r13                ; Clear register (open error)\n"
        "        jmp WFSetIOModeEnd\n"
        "\n"
        "    WFSetIOModeOpenRWFile:      ; Open R/W file mode\n"
        "        mov r12, 5              ; Set file output I/O mode\n"
        "        mov [file_io], 1        ; Set I/O file mode to R/W\n"
        "\n"
        "        mov rax, input_file     ; Load input file handle\n"
        "        test rax, rax           ; Check input file handle\n"
        "        je WFSetIOModeRWOpenInputFileOk\n"
        "            ; Close input file\n"
        "            mov rcx, input_file     ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeRWOpenInputFileOk:\n"
        "\n"
        "        mov rax, output_file    ; Load output file handle\n"
        "        test rax, rax           ; Check output file handle\n"
        "        je WFSetIOModeRWOpenOutputFileOk\n"
        "            ; Close output file\n"
        "            mov rcx, output_file    ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeRWOpenOutputFileOk:\n"
        "\n"
        "        mov rax, rw_file        ; Load R/W file handle\n"
        "        test rax, rax           ; Check R/W  file handle\n"
        "        je WFSetIOModeRWOpenRWFileOk\n"
        "            ; Close R/W file\n"
        "            mov rcx, rw_file        ; Move file handle in rcx\n"
        "            call fclose             ; Close file (handle in rcx)\n"
        "        WFSetIOModeRWOpenRWFileOk:\n"
        "\n"
        "        xor rax, rax                ; Clear rax\n"
        "        mov input_file, rax         ; Clear input file handle\n"
        "        mov output_file, rax        ; Clear output file handle\n"
        "        mov rw_file, rax            ; Clear R/W file handle\n"
        "\n"
        "        lea r8, [r15 + r14*4]       "
        "; Load file path memory address into r8\n"
        "        mov rax, [r8]               ; Move file path into rax\n"
        "        test rax, rax               ; Check file path\n"
        "        je WFSetIOModeRWOpenRWFileErr\n"
        "\n"
        "        ; Copy 4bytes characters string into 1byte characters string\n"
        "        sub rsp, 4096               ; Push stack\n"
        "        mov rbx, rsp                ; Move stack pointer into rbx\n"
        "        mov rcx, 4000               ; Loop for 4000 characters max\n"
        "        WFSetIOModeOpenRWFileCpy:\n"
        "            mov r9, [r8]            ; Move character into r9\n"
        "            mov [rbx], r9           ; Copy character into stack\n"
        "            add r8, 4               ; Increment paht string pointer\n"
        "            inc rbx                 ; Increment destination pointer\n"
        "            test r9, r9             ; Check if character is nul\n"
        "            je WFSetIOModeOpenRWFileDone        ; Copy string done\n"
        "            loop WFSetIOModeOpenRWFileCpy       ; Copy string loop\n"
        "        WFSetIOModeOpenRWFileDone:\n"
        "        xor r9, r9                  ; Clear r9\n"
        "        mov [rbx], r9               ; Add nul character\n"
        "\n"
        "        lea rdx, [rsp]              ; Load file string address\n"
        "        lea r8, file_mode_rw        ; Load mode string address\n"
        "        lea rcx, rw_file            ; Load file handle address\n"
        "        sub rsp, 32                 ; Push stack\n"
        "        ; Open file (handle in rcx, "
        "path str addr in rdx, mode str addr in r8)\n"
        "        call fopen_s                ; Open file\n"
        "        add rsp, 4128               ; Pop stack\n"
        "\n"
        "        mov rcx, rw_file            ; Move file handle in rcx\n"
        "        test rcx, rcx               ; Check file handle\n"
        "        je WFSetIOModeRWOpenRWFileErr\n"
        "            mov r8, 2               ; Move 2 to r8 (SEEK_END)\n"
        "            xor edx, edx            ; Clear edx (cursor position)\n"
        "            ; Set file cursor position "
        "(handle in rcx, position in edx)\n"
        "            call fseek              ; Call fseek\n"
        "            mov r13, 1              "
        "; Set register to 1 (open success)\n"
        "            jmp WFSetIOModeEnd\n"
        "\n"
        "        WFSetIOModeRWOpenRWFileErr:\n"
        "        xor r13, r13                ; Clear register (open error)\n"
        "        jmp WFSetIOModeEnd\n"
        "\n"
        "    WFSetIOModeInputFile:       ; File input mode\n"
        "        mov r12, 4              ; Set file input I/O mode\n"
        "        jmp WFSetIOModeEnd\n"
        "\n"
        "    WFSetIOModeOutputFile:      ; File output mode\n"
        "        mov r12, 5              ; Set file output I/O mode\n"
        "        jmp WFSetIOModeEnd\n"
        "\n"
        "    WFSetIOModeEnd:\n"
        "    mov rax, r13    ; Restore register from r13\n"
        "    add rsp, 48     ; Pop stack (16 bytes boundary)\n"
        "\n"
        "    pop r11         ; Pop main esp\n"
        "    pop r10         ; Pop memory address\n"
        "    pop rdx         ; Pop back pointer\n"
        "    pop rcx         ; Pop pointer\n"
        "    pop rbx         ; Pop back register\n"
        "\n"
        "    ret       ; Return to caller\n"
        "\n"
        "main endp\n"
        "_TEXT ENDS\n"
        "end\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly number constant                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMNumberHead[] =
        "    mov eax, 0";
    const char WFASMNumberFoot[] =
        "h   ; Move number constant into register\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly character constant                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMCharacterHead[] =
        "    mov eax, '";
    const char WFASMCharacterFoot[] =
        "'   ; Move character constant into register\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly string constant                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStringHead[] =
        "\n"
        "    ; String constant\n"
        "    push rax                ; Push rax\n"
        "    xor rax, rax            ; Clear rax\n"
        "    movsxd r9, ecx          ; Convert p into r9\n"
        "    lea r8, [r10 + r9*4]    ; Load memory address into r8\n";
    const char WFASMStringCharacterHead[] =
        "    mov al, '";
    const char WFASMStringCharacterFoot[] =
        "'           ; Write character into al\n"
        "    mov [r8], rax           ; Write character into memory\n"
        "    add r8, 4               ; Increment pointer\n";
    const char WFASMStringFoot[] =
        "    xor rax, rax            ; Clear rax\n"
        "    mov [r8], rax           ; Write nul character into memory\n"
        "    pop rax                 ; Pop rax\n"
        "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly label                                                     //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMLabelHead[] =
        "WF";
    const char WFASMLabelMid[] =
        ":   ; Label :";
    const char WFASMLabelFoot[] =
        ":\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump                                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpHead[] =
        "    jmp WF";
    const char WFASMJumpFoot[] =
        "    ; Jump\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly call                                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMCallHead[] =
        "    call WF";
    const char WFASMCallFoot[] =
        "    ; Call\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump equal to zero                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpEZHead[] =
        "    cmp eax, 0              ; Compare reg with 0\n"
        "    jz WF";
    const char WFASMJumpEZFoot[] =
        "    ; Jump if zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump not equal to zero                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpNZHead[] =
        "    cmp eax, 0              ; Compare reg with 0\n"
        "    jnz WF";
    const char WFASMJumpNZFoot[] =
        "    ; Jump if not zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump greater than zero                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpGZHead[] =
        "    cmp eax, 0              ; Compare reg with 0\n"
        "    jg WF";
    const char WFASMJumpGZFoot[] =
        "    ; Jump if greater than zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump less than zero                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpLZHead[] =
        "    cmp eax, 0              ; Compare reg with 0\n"
        "    jl WF";
    const char WFASMJumpLZFoot[] =
        "    ; Jump if less than zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly return                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMReturn[] =
        "\n"
        "    ; Return to caller\n"
        "    cmp rsp, r11            ; Compare current rsp with main rsp\n"
        "    je WFMainEnd            ; Jump to WFMainEnd if (rsp == r11)\n"
        "    ret                     ; Return to caller\n"
        "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly swap pointers                                             //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSwapPointers[] =
        "    xchg ecx, edx           ; Swap pointer (p <=> q)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly increment pointer                                         //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMIncrementPointer[] =
        "    inc ecx                 ; Increment p\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly decrement pointer                                         //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMDecrementPointer[] =
        "    dec ecx                 ; Decrement p\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly set pointer address                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSetPointerAddress[] =
        "    mov ecx, eax            ; Set pointer address (p = r)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly get pointer address                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMGetPointerAddress[] =
        "    mov eax, ecx            ; Get pointer address (r = p)\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly swap registers                                            //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSwapRegisters[] =
        "    xchg eax, ebx           ; Swap register (r <=> b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly load pointed value                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMLoadPointedValue[] =
        "\n"
        "    ; Load pointed value (r = *p)\n"
        "    movsxd r9, ecx          ; Convert p into r9\n"
        "    lea r8, [r10 + r9*4]    ; Load memory address into r8\n"
        "    mov eax, [r8]           ; Load pointed value into register\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly store register value                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStoreRegisterValue[] =
        "\n"
        "    ; Store register value (*p = r)\n"
        "    movsxd r9, ecx          ; Convert p into r9\n"
        "    lea r8, [r10 + r9*4]    ; Load memory address into r8\n"
        "    mov [r8], eax           ; Store register at pointed address\n"
        "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly add registers                                             //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMAddRegisters[] =
        "    add eax, ebx            ; Add (r = r + b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly subtract registers                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSubtractRegisters[] =
        "    sub eax, ebx            ; Subtract (r = r - b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly multiply registers                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMMultiplyRegisters[] =
        "\n"
        "    ; Multiply (r = r * b)\n"
        "    mov r8, rdx             ; Save rdx into r8\n"
        "    mul ebx                 ; Multiply (r = r * b)\n"
        "    mov rdx, r8             ; Restore rdx from r8\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly divide registers                                          //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMDivideRegisters[] =
        "\n"
        "    ; Divide (r = r / b)\n"
        "    mov r8, rdx             ; Save rdx into r8\n"
        "    xor rdx, rdx            ; Clear rdx\n"
        "    div ebx                 ; Quotient in rax, remainder in rdx\n"
        "    mov rdx, r8             ; Restore rdx from r8\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly modulo registers                                          //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMModuloRegisters[] =
        "\n"
        "    ; Modulo (r = r % b)\n"
        "    mov r8, rdx             ; Save rdx into r8\n"
        "    xor rdx, rdx            ; Clear rdx\n"
        "    div ebx                 ; Quotient in rax, remainder in rdx\n"
        "    mov eax, edx            ; Move remainder into register\n"
        "    mov rdx, r8             ; Restore rdx from r8\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly bitwise and registers                                     //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMAndRegisters[] =
        "    and eax, ebx            ; Bitwise AND (r = r & b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly bitwise or registers                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMOrRegisters[] =
        "    or eax, ebx             ; Bitwise OR (r = r | b)\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly standard input                                            //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStandardInput[] =
        "    call WFStandardInput    ; Standard input\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly standard output                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStandardOutput[] =
        "    call WFStandardOutput   ; Standard output\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly set cursor position                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSetCursorPosition[] =
        "    call WFSetCursorPosition    ; Set cursor position\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly set I/O mode                                              //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSetIOMode[] =
        "    call WFSetIOMode            ; Set I/O mode\n";


#endif // WFC_WINDOWSASM_HEADER
