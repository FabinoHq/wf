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
        "EXTRN ??_U@YAPEAX_K@Z:PROC      ; new[]\n"
        "EXTRN ??_V@YAXPEAX@Z:PROC       ; delete[]\n"
        "\n"
        "PUBLIC main\n"
        "\n"
        "; Data segment\n"
        ".data\n"
        "\n"
        "; Code segment\n"
        ".code\n"
        "_TEXT SEGMENT\n"
        "main proc\n"
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
        "    sub rsp, 40     ; Push stack\n"
        "\n"
        "    ; Allocate memory\n"
        "    mov rcx, 67108864       ; 16777216*4 bytes\n"
        "    call ??_U@YAPEAX_K@Z    ; new[] "
        "(size in rcx, return address in rax)\n"
        "    push rax                ; Push address into stack\n"
        "\n"
        "    ; Set memory pointer\n"
        "    mov r12, rax        ; Move address into r12\n"
        "    add r12, 33554432   ; Add memory offset ((16777216*4)/2 bytes)\n"
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
        "    ; Cleanup memory\n"
        "    pop rcx                     ; Restore address from stack\n"
        "    call ??_V@YAXPEAX@Z         ; delete[] (address in rcx)\n"
        "\n"
        "    ; Wait for keyboard input\n"
        "    waitkeyboard:\n"
        "       sub rsp, 40         ; Push stack\n"
        "       call _kbhit         ; Call _kbhit\n"
        "       add rsp, 40         ; Pop stack\n"
        "       test eax, eax       ; Set ZF to 1 if eax is equal to 0\n"
        "       je waitkeyboard     ; Loop if _kbhit returned 0\n"
        "\n"
        "    ; Get keyboard input\n"
        "    sub rsp, 40         ; Push stack\n"
        "    call _getch         ; Call _getch (get character in al)\n"
        "    add rsp, 40         ; Pop stack\n"
        "\n"
        "    ; End of program\n"
        "    xor rax, rax    ; Clear rax\n"
        "    add rsp, 40     ; Pop stack\n"
        "    ret 0           ; Return 0\n"
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
    //  WF Assembly label                                                     //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMLabelHead[] =
        "    WF";
    const char WFASMLabelFoot[] =
        ":   ; Label\n";

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
        "    cmp eax, 0     ; Compare eax with 0\n"
        "    jz WF";
    const char WFASMJumpEZFoot[] =
        "    ; Jump if zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump not equal to zero                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpNZHead[] =
        "    cmp eax, 0     ; Compare eax with 0\n"
        "    jnz WF";
    const char WFASMJumpNZFoot[] =
        "    ; Jump if not zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump greater than zero                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpGZHead[] =
        "    cmp eax, 0     ; Compare eax with 0\n"
        "    jg WF";
    const char WFASMJumpGZFoot[] =
        "    ; Jump if greater than zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump less than zero                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpLZHead[] =
        "    cmp eax, 0     ; Compare eax with 0\n"
        "    jl WF";
    const char WFASMJumpLZFoot[] =
        "    ; Jump if less than zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly return                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMReturn[] =
        "    ret    ; Return to caller\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly swap pointers                                             //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSwapPointers[] =
        "\n"
        "    ; Swap pointers (p <=> q)\n"
        "    push rcx          ; Push p into stack\n"
        "    mov ecx, edx      ; Move q into p\n"
        "    pop rdx           ; Pop p into q\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly increment pointer                                         //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMIncrementPointer[] =
        "    inc ecx    ; Increment p\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly decrement pointer                                         //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMDecrementPointer[] =
        "    dec ecx    ; Decrement p\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly set pointer address                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSetPointerAddress[] =
        "    mov ecx, eax    ; Set pointer address (p = r)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly get pointer address                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMGetPointerAddress[] =
        "    mov eax, ecx    ; Get pointer address (r = p)\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly swap registers                                            //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSwapRegisters[] =
        "\n"
        "    ; Swap register (r <=> b)\n"
        "    push rax          ; Push r into stack\n"
        "    mov eax, ebx      ; Move b into r\n"
        "    pop rbx           ; Pop r into b\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly load pointed value                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMLoadPointedValue[] =
        "\n"
        "    ; Load pointed value (r = *p)\n"
        "    mov r8, r12        ; Move memory array address into r8\n"
        "    movsxd r9, ecx     ; Convert pointer value into r9 \n"
        "    add r8, r9         ; Add pointer value to r8\n"
        "    mov eax, [r8]      ; Load pointed value into register\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly store register value                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStoreRegisterValue[] =
        "\n"
        "    ; Store register value (*p = r)\n"
        "    mov r8, r12        ; Move memory array address into r8\n"
        "    movsxd r9, ecx     ; Convert pointer value into r9 \n"
        "    add r8, r9         ; Add pointer value to r8\n"
        "    mov [r8], eax      ; Store register at pointed address\n"
        "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly add registers                                             //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMAddRegisters[] =
        "    add eax, ebx   ; Add (r = r + b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly subtract registers                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSubtractRegisters[] =
        "    sub eax, ebx   ; Subtract (r = r - b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly multiply registers                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMMultiplyRegisters[] =
        "    mul ebx       ; Multiply (r = r * b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly divide registers                                          //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMDivideRegisters[] =
        "\n"
        "    ; Divide (r = r / b)\n"
        "    push rdx       ; Push rdx\n"
        "    div ebx        ; Quotient in rax, remainder in rdx\n"
        "    pop rdx        ; Pop rdx\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly modulo registers                                          //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMModuloRegisters[] =
        "\n"
        "    ; Modulo (r = r % b)\n"
        "    push rdx       ; Push rdx\n"
        "    div ebx        ; Quotient in rax, remainder in rdx\n"
        "    mov eax, edx   ; Move remainder into register\n"
        "    pop rdx        ; Pop rdx\n"
        "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly standard output                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStandardOutput[] =
        "\n"
        "    ; Standard output\n"
        "    push rax        ; Push rax\n"
        "    push rbx        ; Push rbx\n"
        "    push rcx        ; Push rcx\n"
        "    push rdx        ; Push rdx\n"
        "    push r12        ; Push r12\n"
        "\n"
        "    mov cl, al      ; Move register value into cl\n"
        "    sub rsp, 40     ; Push stack\n"
        "    call putchar    ; Output character from cl\n"
        "    add rsp, 40     ; Pop stack;\n"
        "\n"
        "    pop r12         ; Pop r12\n"
        "    pop rdx         ; Pop rdx\n"
        "    pop rcx         ; Pop rcx\n"
        "    pop rbx         ; Pop rbx\n"
        "    pop rax         ; Pop rax\n"
        "\n";

#endif // WFC_WINDOWSASM_HEADER
