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


////////////////////////////////////////////////////////////////////////////////
//  Windows system functions                                                  //
////////////////////////////////////////////////////////////////////////////////
#ifdef WFP_WINDOWS

    #include <windows.h>
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

    ////////////////////////////////////////////////////////////////////////////
    //  Windows get terminal cursor position                                  //
    ////////////////////////////////////////////////////////////////////////////
    void WFGetTerminalCursor(int32_t& x, int32_t& y)
    {
        // Flush standard output
        static const HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        std::cout.flush();

        // Reset coords
        x = 0;
        y = 0;
        COORD coords = { 0, 0 };

        // Get cursor position
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(stdHandle, &consoleInfo))
        {
            x = static_cast<int32_t>(consoleInfo.dwCursorPosition.X);
            y = static_cast<int32_t>(consoleInfo.dwCursorPosition.Y);
        }

        // Clamp x and y
        if (x <= 0) x = 0;
        if (y <= 0) y = 0;
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Windows set terminal cursor position                                  //
    ////////////////////////////////////////////////////////////////////////////
    void WFSetTerminalCursor(int32_t x, int32_t y)
    {
        // Clamp x and y
        if (x <= 0) x = 0;
        if (y <= 0) y = 0;

        // Flush standard output
        static const HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        std::cout.flush();

        // Set cursor position
        COORD coords = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(stdHandle, coords);
    }

#endif // WFP_WINDOWS


////////////////////////////////////////////////////////////////////////////////
//  Linux system functions                                                    //
////////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////
    //  Linux get terminal cursor position                                    //
    ////////////////////////////////////////////////////////////////////////////
    void WFGetTerminalCursor(int32_t& x, int32_t& y)
    {
        // Reset coords
        x = 0;
        y = 0;

        // Flush standard output
        std::cout.flush();

        // Get current termios
        struct termios cur_termios = {0, 0, 0, 0, 0, {0}, 0, 0};
        if (tcgetattr(0, &cur_termios) < 0) return;

        // Turn off canonical and echo mode
        cur_termios.c_lflag &= ~ICANON;
        cur_termios.c_lflag &= ~ECHO;
        cur_termios.c_cc[VMIN] = 1;
        cur_termios.c_cc[VTIME] = 0;

        // Set termios
        if (tcsetattr(0, TCSANOW, &cur_termios) < 0) return;

        // Get cursor position
        write(1, "\033[6n", 4);

        // Read cursor position
        std::string position = "";
        char ch = 0;
        while (ch != ';')
        {
            if (!read(0, &ch, 1)) break;
            if (std::isdigit(ch))
            {
                position.push_back(ch);
            }
        }
        try { y = std::stoi(position, 0, 10); }
        catch (...) { y = 0; }
        position = "";
        ch = 0;
        while (ch != 'R')
        {
            if (!read(0, &ch, 1)) break;
            if (std::isdigit(ch))
            {
                position.push_back(ch);
            }
        }
        try { x = std::stoi(position, 0, 10); }
        catch (...) { x = 0; }

        // Clamp x and y
        --x;
        --y;
        if (x <= 0) x = 0;
        if (y <= 0) y = 0;

        // Restore termios
        cur_termios.c_lflag |= ICANON;
        cur_termios.c_lflag |= ECHO;
        tcsetattr(0, TCSADRAIN, &cur_termios);
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Linux set terminal cursor position                                    //
    ////////////////////////////////////////////////////////////////////////////
    void WFSetTerminalCursor(int32_t x, int32_t y)
    {
        // Clamp x and y
        ++x;
        ++y;
        if (x <= 0) x = 0;
        if (y <= 0) y = 0;

        // Flush standard output
        std::cout.flush();

        // Set cursor position
        std::cout << "\033[" << y << ";" << x << "f";

        // Flush standard output
        std::cout.flush();
    }

#endif // WFP_LINUX
