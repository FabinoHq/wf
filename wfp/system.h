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
//    WFP : WF Parser                                                         //
//     system.h : WFP System management wrapper                               //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFP_SYSTEM_HEADER
#define WFP_SYSTEM_HEADER


    ////////////////////////////////////////////////////////////////////////////
    //  Operating system configuration                                        //
    ////////////////////////////////////////////////////////////////////////////
    #if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
        #define WFP_WINDOWS
    #endif // Windows

    #if defined(__APPLE__)
        #define WFP_MACOS
    #endif // MacOS

    #if defined(__linux__)
        #define WFP_LINUX
    #endif // Linux


    ////////////////////////////////////////////////////////////////////////////
    //  64bits or 32bits configuration                                        //
    ////////////////////////////////////////////////////////////////////////////
    #if defined(__x86_64__) || defined(_WIN64) || defined(__LP64__) || \
        defined(__ia64) || defined(_M_X64) || defined(_M_IA64) || \
        defined(__aarch64__) || defined(__powerpc64__)
        #define WFP_64BITS
    #else
        #define WFP_32BITS
    #endif


#endif // WFP_SYSTEM_HEADER
