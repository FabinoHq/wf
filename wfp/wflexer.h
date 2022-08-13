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
//     wflexer.h : WFP Lexer                                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef WFP_WFLEXER_HEADER
#define WFP_WFLEXER_HEADER

    #include "system.h"

    #include <cstdint>
    #include <cstring>
    #include <exception>
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cctype>
    #include <algorithm>
    #include <unordered_map>


    ////////////////////////////////////////////////////////////////////////////
    //  WF program file structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct WfProgramFile
    {
        std::ifstream file;
        std::string path;
        int32_t line;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  WfLexer main class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class WfLexer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  WfLexer default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            WfLexer(std::unordered_map<std::string, bool>& includes,
                std::unordered_map<std::string, int32_t>& labels);

            ////////////////////////////////////////////////////////////////////
            //  WfLexer destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~WfLexer();


            ////////////////////////////////////////////////////////////////////
            //  WF program lexing                                             //
            //  param path : Path of the .wf program to analyze               //
            //  return : True if the .wf program is successfully analyzed     //
            ////////////////////////////////////////////////////////////////////
            bool lexer(char* program, const std::string& path);


        private:
            ////////////////////////////////////////////////////////////////////
            //  WfLexer private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            WfLexer(const WfLexer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  WfLexer private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            WfLexer& operator=(const WfLexer&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Analyze WF program                                            //
            //  param path : Path of the .wf program to analyze               //
            //  return : True if the .wf program is successfully analyzed     //
            ////////////////////////////////////////////////////////////////////
            bool analyze(const std::string& path);

            ////////////////////////////////////////////////////////////////////
            //  Analyze line count                                            //
            //  param wfprogram : WF program to analyze line count from       //
            //  return : True if line count is successfully analyzed          //
            ////////////////////////////////////////////////////////////////////
            bool analyzeLineCount(WfProgramFile& wfprogram, char& ch);

            ////////////////////////////////////////////////////////////////////
            //  Analyze include                                               //
            //  param wfprogram : WF program to analyze include from          //
            //  return : True if include is successfully analyzed             //
            ////////////////////////////////////////////////////////////////////
            bool analyzeInclude(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Analyze comment                                               //
            //  param wfprogram : WF program to analyze comment from          //
            //  return : True if comment is successfully analyzed             //
            ////////////////////////////////////////////////////////////////////
            bool analyzeComment(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Analyze number constant                                       //
            //  param wfprogram : WF program to analyze number from           //
            //  return : True if number is successfully analyzed              //
            ////////////////////////////////////////////////////////////////////
            bool analyzeNumber(WfProgramFile& wfprogram, char digit);

            ////////////////////////////////////////////////////////////////////
            //  Analyze character constant                                    //
            //  param wfprogram : WF program to analyze character from        //
            //  return : True if character is successfully analyzed           //
            ////////////////////////////////////////////////////////////////////
            bool analyzeCharacter(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Analyze string constant                                       //
            //  param wfprogram : WF program to analyze string from           //
            //  return : True if string is successfully analyzed              //
            ////////////////////////////////////////////////////////////////////
            bool analyzeString(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Analyze label                                                 //
            //  param wfprogram : WF program to analyze label from            //
            //  return : True if label is successfully analyzed               //
            ////////////////////////////////////////////////////////////////////
            bool analyzeLabel(WfProgramFile& wfprogram, char type);

            ////////////////////////////////////////////////////////////////////
            //  Write character into program                                  //
            //  param ch : Character to add to the program                    //
            //  return : True if the character is successfully written        //
            ////////////////////////////////////////////////////////////////////
            bool writeProgram(char ch);

            ////////////////////////////////////////////////////////////////////
            //  Check label jumps                                             //
            //  return : True if label jumps are successfully checked         //
            ////////////////////////////////////////////////////////////////////
            bool checkLabelJumps();


        private:
            char*           m_program;              // Program array
            int32_t         m_cursor;               // Program cursor

            std::unordered_map<std::string, bool>&      m_includes; // Includes
            std::unordered_map<std::string, int32_t>&   m_labels;   // Labels
    };


#endif // WFP_WFLEXER_HEADER
