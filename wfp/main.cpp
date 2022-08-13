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
//     main.cpp : Main program entry point                                    //
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "wfp.h"
#include <filesystem>
#include <iostream>
#include <exception>


////////////////////////////////////////////////////////////////////////////////
//  Standard program entry point                                              //
//  return : Main program return code                                         //
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    try
    {
        // Set working directory
        std::string directory = argv[1];
        size_t i = 0;
        for (i = directory.length()-1; i > 0; --i)
        {
            if ((directory[i] == '/') || (directory[i] == '\\'))
            {
                ++i;
                break;
            }
        }
        directory = directory.substr(0, i);
        if (!directory.empty())
        {
            std::filesystem::current_path(directory);
        }
    }
    catch (std::filesystem::filesystem_error&)
    {
        // Unable to set working directory
    }
    catch (...)
    {
        // Unable to set working directory
    }

    if (argc >= 2)
    {
        try
        {
            // Start WFP
            Wfp wfp;
            wfp.launch(argv[1]);
        }
        catch (const std::exception&)
        {
            // Standard exception occured
            std::cerr << "Unknown error occured\n";
        }
        catch (...)
        {
            // Unknown exception occured
            std::cerr << "Unknown error occured\n";
        }
    }
    else
    {
        // Not enough program arguments
        std::cerr << "Error : Please specify a .wf input file\n";
    }

    // Wait for a keyboard input
    #ifdef WFP_WINDOWS
        WFKeyboardInput();
    #endif // WFP_WINDOWS

    // Program successfully executed
    return 0;
}
