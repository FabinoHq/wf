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
    //  WFC assembly                                                          //
    ////////////////////////////////////////////////////////////////////////////
    #ifdef WFC_WINDOWS
        #include "windowsasm.h"
    #endif // WFC_WINDOWS

    #ifdef WFC_LINUX
        #include "linuxasm.h"
    #endif // WFC_LINUX


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
            //  return : True if WF is successfully compiled, false otherwise //
            ////////////////////////////////////////////////////////////////////
            bool run();


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


            ////////////////////////////////////////////////////////////////////
            //  Write WF header                                               //
            //  return : True if WF header is successfully written            //
            ////////////////////////////////////////////////////////////////////
            bool writeHeader();

            ////////////////////////////////////////////////////////////////////
            //  Write WF footer                                               //
            //  return : True if WF footer is successfully written            //
            ////////////////////////////////////////////////////////////////////
            bool writeFooter();


            ////////////////////////////////////////////////////////////////////
            //  Write WF number                                               //
            //  return : True if WF number is successfully written            //
            ////////////////////////////////////////////////////////////////////
            bool writeNumber(int64_t num);

            ////////////////////////////////////////////////////////////////////
            //  Write WF character                                            //
            //  return : True if WF character is successfully written         //
            ////////////////////////////////////////////////////////////////////
            bool writeCharacter(char ch);


            ////////////////////////////////////////////////////////////////////
            //  Write WF swap pointers                                        //
            //  return : True if WF swap pointers is successfully written     //
            ////////////////////////////////////////////////////////////////////
            bool writeSwapPointers();

            ////////////////////////////////////////////////////////////////////
            //  Write WF increment pointer                                    //
            //  return : True if WF inc pointer is successfully written       //
            ////////////////////////////////////////////////////////////////////
            bool writeIncrementPointer();

            ////////////////////////////////////////////////////////////////////
            //  Write WF decrement pointer                                    //
            //  return : True if WF dec pointer is successfully written       //
            ////////////////////////////////////////////////////////////////////
            bool writeDecrementPointer();

            ////////////////////////////////////////////////////////////////////
            //  Write WF set pointer address                                  //
            //  return : True if WF set pointer is successfully written       //
            ////////////////////////////////////////////////////////////////////
            bool writeSetPointerAddress();

            ////////////////////////////////////////////////////////////////////
            //  Write WF get pointer address                                  //
            //  return : True if WF get pointer is successfully written       //
            ////////////////////////////////////////////////////////////////////
            bool writeGetPointerAddress();


            ////////////////////////////////////////////////////////////////////
            //  Write WF swap registers                                       //
            //  return : True if WF swap registers is successfully written    //
            ////////////////////////////////////////////////////////////////////
            bool writeSwapRegisters();

            ////////////////////////////////////////////////////////////////////
            //  Write WF load pointed value                                   //
            //  return : True if WF load value is successfully written        //
            ////////////////////////////////////////////////////////////////////
            bool writeLoadPointedValue();

            ////////////////////////////////////////////////////////////////////
            //  Write WF store register value                                 //
            //  return : True if WF store value is successfully written       //
            ////////////////////////////////////////////////////////////////////
            bool writeStoreRegisterValue();


            ////////////////////////////////////////////////////////////////////
            //  Write WF add registers                                        //
            //  return : True if WF add registers is successfully written     //
            ////////////////////////////////////////////////////////////////////
            bool writeAddRegisters();

            ////////////////////////////////////////////////////////////////////
            //  Write WF subtract registers                                   //
            //  return : True if WF subtract is successfully written          //
            ////////////////////////////////////////////////////////////////////
            bool writeSubtractRegisters();


            ////////////////////////////////////////////////////////////////////
            //  Write WF output                                               //
            //  return : True if WF output is successfully written            //
            ////////////////////////////////////////////////////////////////////
            bool writeOutput();


        private:
            char*               m_program;          // Program array
            int32_t             m_cursor;           // Program cursor

            std::unordered_map<std::string, bool>       m_includes; // Includes
            std::unordered_map<std::string, int32_t>    m_labels;   // Labels

            WfLexer             m_wflexer;          // WF Lexer

            std::ofstream       m_output;           // Assembly output
    };


#endif // WFC_WFC_HEADER
