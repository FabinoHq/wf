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
//     wfp.h : WFP Main Interpreter                                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFP_WFP_HEADER
#define WFP_WFP_HEADER

    #include "system.h"

    #include <cctype>
    #include <cstdint>
    #include <cstring>
    #include <unordered_map>
    #include <exception>
    #include <iostream>
    #include <fstream>
    #include <string>


    ////////////////////////////////////////////////////////////////////////////
    //  WFP default settings                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const bool WFMemoryDump = true;
    const int32_t WFProgramSize = 16777216;
    const int32_t WFProgramOverhead = 1024;
    const int32_t WFMemorySize = 16777216;
    const int32_t WFMemoryOffset = WFMemorySize/2;


    ////////////////////////////////////////////////////////////////////////////
    //  WFP program file structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct WfProgramFile
    {
        std::ifstream file;
        std::string path;
        int32_t line;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  WFP main class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Wfp
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Wfp default constructor                                       //
            ////////////////////////////////////////////////////////////////////
            Wfp();

            ////////////////////////////////////////////////////////////////////
            //  Wfp destructor                                                //
            ////////////////////////////////////////////////////////////////////
            ~Wfp();


            ////////////////////////////////////////////////////////////////////
            //  Launch WFP                                                    //
            //  param path : Path of the .wf program to run                   //
            //  return : True if WFP successfully started, false otherwise    //
            ////////////////////////////////////////////////////////////////////
            bool launch(const std::string& path);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess WF program                                         //
            //  param path : Path of the .wf program to preprocess            //
            //  return : True if the .wf program is successfully preprocessed //
            ////////////////////////////////////////////////////////////////////
            bool preprocess(const std::string& path);

            ////////////////////////////////////////////////////////////////////
            //  Run WFP                                                       //
            ////////////////////////////////////////////////////////////////////
            void run();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Wfp private copy constructor : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Wfp(const Wfp&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Wfp private copy operator : Not copyable                      //
            ////////////////////////////////////////////////////////////////////
            Wfp& operator=(const Wfp&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Preprocess comment                                            //
            //  param wfprogram : WF program to preprocess comment from       //
            //  return : True if WF comment is successfully preprocessed      //
            ////////////////////////////////////////////////////////////////////
            bool preprocessComment(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess include                                            //
            //  param wfprogram : WF program to preprocess include from       //
            //  return : True if WF include is successfully preprocessed      //
            ////////////////////////////////////////////////////////////////////
            bool preprocessInclude(WfProgramFile& wfprogram);


        private:
            char*           m_program;              // Program array
            int32_t         m_cursor;               // Program cursor
            int32_t*        m_memory;               // Memory array
            int32_t*        m_pointer;              // Main pointer
            int32_t*        m_backpointer;          // Back pointer
            int32_t         m_register;             // Main register
            int32_t         m_backregister;         // Back register

            std::unordered_map<std::string, bool>       m_includes; // Includes
            std::unordered_map<std::string, int32_t>    m_labels;   // Labels
    };


#endif // WFP_WFP_HEADER
