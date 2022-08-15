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
        "    mov r12, rax       ; Move p into r12\n"
        "    add r12, 33554432  ; Add memory offset ((16777216*4)/2 bytes)\n"
        "\n"
        "    xor rax, rax    ; Clear rax  :  Register \n"
        "    xor rbx, rbx    ; Clear rbx  :  Back register\n"
        "    xor rcx, rcx    ; Clear rcx  :  Pointer \n"
        "    xor rdx, rdx    ; Clear rdx  :  Back pointer\n"
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
        "    ; End of program\n"
        "    xor rax, rax    ; Clear rax\n"
        "    add rsp, 40     ; Pop stack\n"
        "    ret 0           ; Return 0\n"
        "\n"
        "main endp\n"
        "_TEXT ENDS\n"
        "end\n";


#endif // WFC_WINDOWSASM_HEADER
