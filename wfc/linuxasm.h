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
//     linuxasm.h : WFC Linux assembly                                        //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFC_LINUXASM_HEADER
#define WFC_LINUXASM_HEADER


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
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly footer                                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMFooter[] = "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly number constant                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMNumberHead[] =
        "    ";
    const char WFASMNumberFoot[] =
        "   ; Move number constant into register\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly character constant                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMCharacterHead[] =
        "    ";
    const char WFASMCharacterFoot[] =
        "   ; Move character constant into register\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly string constant                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStringHead[] =
        "\n"
        "    ; String constant\n";
    const char WFASMStringCharacterHead[] =
        "    ";
    const char WFASMStringCharacterFoot[] =
        "       ; Write character into al\n";
    const char WFASMStringFoot[] =
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
        "    ; Compare eax with 0\n"
        "    jz WF";
    const char WFASMJumpEZFoot[] =
        "    ; Jump if zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump not equal to zero                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpNZHead[] =
        "    ; Compare eax with 0\n"
        "    jnz WF";
    const char WFASMJumpNZFoot[] =
        "    ; Jump if not zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump greater than zero                                    //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpGZHead[] =
        "    ; Compare eax with 0\n"
        "    jg WF";
    const char WFASMJumpGZFoot[] =
        "    ; Jump if greater than zero\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly jump less than zero                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMJumpLZHead[] =
        "    ; Compare eax with 0\n"
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
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly increment pointer                                         //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMIncrementPointer[] =
        "    ; Increment p\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly decrement pointer                                         //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMDecrementPointer[] =
        "    ; Decrement p\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly set pointer address                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSetPointerAddress[] =
        "    ; Set pointer address (p = r)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly get pointer address                                       //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMGetPointerAddress[] =
        "    ; Get pointer address (r = p)\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly swap registers                                            //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSwapRegisters[] =
        "\n"
        "    ; Swap register (r <=> b)\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly load pointed value                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMLoadPointedValue[] =
        "\n"
        "    ; Load pointed value (r = *p)\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly store register value                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStoreRegisterValue[] =
        "\n"
        "    ; Store register value (*p = r)\n"
        "\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly add registers                                             //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMAddRegisters[] =
        "    ; Add (r = r + b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly subtract registers                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMSubtractRegisters[] =
        "    ; Subtract (r = r - b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly multiply registers                                        //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMMultiplyRegisters[] =
        "    ; Multiply (r = r * b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly divide registers                                          //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMDivideRegisters[] =
        "\n"
        "    ; Divide (r = r / b)\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly modulo registers                                          //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMModuloRegisters[] =
        "\n"
        "    ; Modulo (r = r % b)\n"
        "\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly bitwise and registers                                     //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMAndRegisters[] =
        "    ; Bitwise AND (r = r & b)\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly bitwise or registers                                      //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMOrRegisters[] =
        "    ; Bitwise OR (r = r | b)\n";


    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly standard input                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStandardInput[] =
        "    ; Standard input\n";

    ////////////////////////////////////////////////////////////////////////////
    //  WF Assembly standard output                                           //
    ////////////////////////////////////////////////////////////////////////////
    const char WFASMStandardOutput[] =
        "    ; Standard output\n";


#endif // WFC_LINUXASM_HEADER
