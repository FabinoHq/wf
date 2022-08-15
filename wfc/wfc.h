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
//     wfc.h : WFC Main Interpreter                                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFC_WFC_HEADER
#define WFC_WFC_HEADER

    #include "system.h"
    #include "wflexer.h"

    #include <cstdint>
    #include <cstring>
    #include <exception>
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cctype>
    #include <algorithm>
    #include <unordered_map>
    #include <stack>


    ////////////////////////////////////////////////////////////////////////////
    //  WF I/O mode enumeration                                               //
    ////////////////////////////////////////////////////////////////////////////
    enum WFIOMode
    {
        WF_IOMODE_STANDARD = 0x00,
        WF_IOMODE_FILE_INPUT = 0x01,
        WF_IOMODE_FILE_OUTPUT = 0x02
    };

    ////////////////////////////////////////////////////////////////////////////
    //  WF I/O file state enumeration                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum WFIOFile
    {
        WF_IOFILE_IO = 0x00,
        WF_IOFILE_RW = 0x01
    };


    ////////////////////////////////////////////////////////////////////////////
    //  WFC main class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Wfc
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Wfc default constructor                                       //
            ////////////////////////////////////////////////////////////////////
            Wfc();

            ////////////////////////////////////////////////////////////////////
            //  Wfc destructor                                                //
            ////////////////////////////////////////////////////////////////////
            ~Wfc();


            ////////////////////////////////////////////////////////////////////
            //  Launch WFC                                                    //
            //  param path : Path of the .wf program to run                   //
            //  return : True if WFC successfully started, false otherwise    //
            ////////////////////////////////////////////////////////////////////
            bool launch(const std::string& path);

            ////////////////////////////////////////////////////////////////////
            //  Run WFC                                                       //
            ////////////////////////////////////////////////////////////////////
            void run();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Wfc private copy constructor : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Wfc(const Wfc&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Wfc private copy operator : Not copyable                      //
            ////////////////////////////////////////////////////////////////////
            Wfc& operator=(const Wfc&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Parse number constant                                         //
            ////////////////////////////////////////////////////////////////////
            void parseNumber();

            ////////////////////////////////////////////////////////////////////
            //  Parse character constant                                      //
            ////////////////////////////////////////////////////////////////////
            void parseCharacter();

            ////////////////////////////////////////////////////////////////////
            //  Parse string constant                                         //
            ////////////////////////////////////////////////////////////////////
            void parseString();

            ////////////////////////////////////////////////////////////////////
            //  Parse label                                                   //
            ////////////////////////////////////////////////////////////////////
            void parseLabel();

            ////////////////////////////////////////////////////////////////////
            //  Parse instruction                                             //
            ////////////////////////////////////////////////////////////////////
            void parseInstruction();


        private:
            char*               m_program;          // Program array
            int32_t             m_cursor;           // Program cursor

            std::unordered_map<std::string, bool>       m_includes; // Includes
            std::unordered_map<std::string, int32_t>    m_labels;   // Labels

            WfLexer         m_wflexer;              // WF Lexer
    };


#endif // WFC_WFC_HEADER
