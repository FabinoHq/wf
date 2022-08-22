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
//     system.cpp : WFC System management wrapper                             //
////////////////////////////////////////////////////////////////////////////////
#include "system.h"


////////////////////////////////////////////////////////////////////////////////
//  Windows system functions                                                  //
////////////////////////////////////////////////////////////////////////////////
#ifdef WFC_WINDOWS

    #include <windows.h>
    #include <stdlib.h>
    #include <conio.h>

    ////////////////////////////////////////////////////////////////////////////
    //  Windows low level keyboard input                                      //
    ////////////////////////////////////////////////////////////////////////////
    int WFKeyboardInput()
    {
        // Wait for a keyboard input
        while (!_kbhit());

        // Get the input key code
        int ch = _getch();

        // Handle special key codes
        if (ch == 0)
        {
            switch (_getch())
            {
                case 59:    return 266;     // F1
                case 60:    return 267;     // F2
                case 61:    return 268;     // F3
                case 62:    return 269;     // F4
                case 63:    return 270;     // F5
                case 64:    return 271;     // F6
                case 65:    return 272;     // F7
                case 66:    return 273;     // F8
                case 71:    return 260;     // Numpad Home
                case 72:    return 256;     // Numpad Up arrow
                case 73:    return 264;     // Numpad Page up
                case 75:    return 258;     // Numpad Left arrow
                case 77:    return 259;     // Numpad Right arrow
                case 79:    return 261;     // Numpad End
                case 80:    return 257;     // Numpad Down arrow
                case 81:    return 265;     // Numpad Page down
                default:    break;
            }
        }
        else if (ch == 224)
        {
            switch (_getch())
            {
                case 71:    return 260;     // Home
                case 72:    return 256;     // Up arrow
                case 73:    return 264;     // Page up
                case 75:    return 258;     // Left arrow
                case 77:    return 259;     // Right arrow
                case 79:    return 261;     // End
                case 80:    return 257;     // Down arrow
                case 81:    return 265;     // Page down
                case 82:    return 262;     // Insert
                case 83:    return 263;     // Del
                default:    break;
            }
        }
        else if (ch == 13)
        {
            // Enter
            return 10;
        }

        // Return key code
        return ch;
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

#endif // WFC_WINDOWS


////////////////////////////////////////////////////////////////////////////////
//  Linux system functions                                                    //
////////////////////////////////////////////////////////////////////////////////
#ifdef WFC_LINUX

    #include <unistd.h>
    #include <termios.h>

    ////////////////////////////////////////////////////////////////////////////
    //  Linux low level keyboard input                                        //
    ////////////////////////////////////////////////////////////////////////////
    int WFKeyboardInput()
    {
        // Get current termios
        struct termios cur_termios = {0, 0, 0, 0, 0, {0}, 0, 0};
        if (tcgetattr(0, &cur_termios) < 0) return -1;

        // Turn off canonical and echo mode
        cur_termios.c_lflag &= ~ICANON;
        cur_termios.c_lflag &= ~ECHO;
        cur_termios.c_cc[VMIN] = 1;
        cur_termios.c_cc[VTIME] = 0;

        // Set termios
        if (tcsetattr(0, TCSANOW, &cur_termios) < 0) return -1;

        // Wait for a keyboard input and read the key code
        int64_t ch = 0;
        if (read(0, &ch, 8) < 0) return -1;

        // Handle special key codes
        if ((ch & 0xFF) == 27)
        {
            if (((ch >> 8) & 0xFF) == 79)
            {
                switch ((ch >> 16) & 0xFF)
                {
                    case 80:    ch = 266;       break;      // F1
                    case 81:    ch = 267;       break;      // F2
                    case 82:    ch = 268;       break;      // F3
                    case 83:    ch = 269;       break;      // F4
                    default:    ch = 27;        break;
                }
            }
            else if (((ch >> 8) & 0xFF) == 91)
            {
                switch ((ch >> 16) & 0xFF)
                {
                    case 49:
                        switch ((ch >> 24) & 0xFF)
                        {
                            case 53:    ch = 270;       break;      // F5
                            case 55:    ch = 271;       break;      // F6
                            case 56:    ch = 272;       break;      // F7
                            case 57:    ch = 273;       break;      // F8
                            default:    ch = 27;        break;
                        }
                        break;
                    case 50:    ch = 262;       break;      // Insert
                    case 51:    ch = 263;       break;      // Del
                    case 53:    ch = 264;       break;      // Page Up
                    case 54:    ch = 265;       break;      // Page Down
                    case 65:    ch = 256;       break;      // Up arrow
                    case 66:    ch = 257;       break;      // Down arrow
                    case 67:    ch = 259;       break;      // Right arrow
                    case 68:    ch = 258;       break;      // Left arrow
                    case 70:    ch = 261;       break;      // End
                    case 72:    ch = 260;       break;      // Home
                    default:    ch = 27;        break;
                }
            }
        }
        else if ((ch & 0xFF) == 127)
        {
            // Backspace
            ch = 8;
        }

        // Restore termios
        cur_termios.c_lflag |= ICANON;
        cur_termios.c_lflag |= ECHO;
        tcsetattr(0, TCSADRAIN, &cur_termios);

        // Return key code
        return (ch & 0xFFFFFFFF);
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

#endif // WFC_LINUX
