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
//     system.h : WFC System management wrapper                               //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFC_SYSTEM_HEADER
#define WFC_SYSTEM_HEADER

    #include <cstdint>
    #include <string>
    #include <iostream>
    #include <exception>


    ////////////////////////////////////////////////////////////////////////////
    //  WF program default settings                                           //
    ////////////////////////////////////////////////////////////////////////////
    const int32_t WFProgramSize = 16777216;
    const int32_t WFProgramOverhead = 1024;
    const int32_t WFMemorySize = 16777216;
    const int32_t WFMemoryOffset = WFMemorySize/2;


    ////////////////////////////////////////////////////////////////////////////
    //  Operating system configuration                                        //
    ////////////////////////////////////////////////////////////////////////////
    #if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
        #define WFC_WINDOWS
    #endif // Windows

    #if defined(__APPLE__)
        #define WFC_MACOS
    #endif // MacOS

    #if defined(__linux__)
        #define WFC_LINUX
    #endif // Linux


    ////////////////////////////////////////////////////////////////////////////
    //  64bits or 32bits configuration                                        //
    ////////////////////////////////////////////////////////////////////////////
    #if defined(__x86_64__) || defined(_WIN64) || defined(__LP64__) || \
        defined(__ia64) || defined(_M_X64) || defined(_M_IA64) || \
        defined(__aarch64__) || defined(__powerpc64__)
        #define WFC_64BITS
    #else
        #define WFC_32BITS
    #endif


    ////////////////////////////////////////////////////////////////////////////
    //  Low level keyboard input                                              //
    ////////////////////////////////////////////////////////////////////////////
    char WFKeyboardInput();

    ////////////////////////////////////////////////////////////////////////////
    //  Get terminal cursor position                                          //
    ////////////////////////////////////////////////////////////////////////////
    void WFGetTerminalCursor(int32_t& x, int32_t& y);

    ////////////////////////////////////////////////////////////////////////////
    //  Set terminal cursor position                                          //
    ////////////////////////////////////////////////////////////////////////////
    void WFSetTerminalCursor(int32_t x, int32_t y);


#endif // WFC_SYSTEM_HEADER
