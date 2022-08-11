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
//     system.cpp : WFP System management wrapper                             //
////////////////////////////////////////////////////////////////////////////////
#include "system.h"


#ifdef WFP_WINDOWS

    #include <stdlib.h>
    #include <conio.h>

    ////////////////////////////////////////////////////////////////////////////
    //  Windows low level keyboard input                                      //
    ////////////////////////////////////////////////////////////////////////////
    char WFKeyboardInput()
    {
        // Wait for a keyboard input
        while (!_kbhit());

        // Return the key code
        return _getch();
    }

#endif // WFP_WINDOWS


#ifdef WFP_LINUX

    #include <unistd.h>
    #include <termios.h>

    ////////////////////////////////////////////////////////////////////////////
    //  Linux low level keyboard input                                        //
    ////////////////////////////////////////////////////////////////////////////
    char WFKeyboardInput()
    {
        // Get current termios
        struct termios cur_termios = {0, 0, 0, 0, 0, {0}, 0, 0};
        if (tcgetattr(0, &cur_termios) < 0) return 0;

        // Turn off canonical and echo mode
        cur_termios.c_lflag &= ~ICANON;
        cur_termios.c_lflag &= ~ECHO;
        cur_termios.c_cc[VMIN] = 1;
        cur_termios.c_cc[VTIME] = 0;

        // Set termios
        if (tcsetattr(0, TCSANOW, &cur_termios) < 0) return 0;

        // Wait for a keyboard input and read the keycode
        char ch = 0;
        if (read(0, &ch, 1) < 0) return 0;

        // Restore termios
        cur_termios.c_lflag |= ICANON;
        cur_termios.c_lflag |= ECHO;
        tcsetattr(0, TCSADRAIN, &cur_termios);

        // Return keycode
        return ch;
    }

#endif // WFP_LINUX
