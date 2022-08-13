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

    #include <cctype>
    #include <cstdint>
    #include <cstring>
    #include <exception>
    #include <iostream>
    #include <fstream>
    #include <string>
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

            ////////////////////////////////////////////////////////////////////
            //  Preprocess WF program                                         //
            //  param path : Path of the .wf program to preprocess            //
            //  return : True if the .wf program is successfully preprocessed //
            ////////////////////////////////////////////////////////////////////
            bool preprocess(const std::string& path);


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
            //  Preprocess line count                                         //
            //  param wfprogram : WF program to preprocess line count from    //
            //  return : True if line count is successfully preprocessed      //
            ////////////////////////////////////////////////////////////////////
            bool preprocessLineCount(WfProgramFile& wfprogram, char& ch);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess include                                            //
            //  param wfprogram : WF program to preprocess include from       //
            //  return : True if include is successfully preprocessed         //
            ////////////////////////////////////////////////////////////////////
            bool preprocessInclude(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess comment                                            //
            //  param wfprogram : WF program to preprocess comment from       //
            //  return : True if comment is successfully preprocessed         //
            ////////////////////////////////////////////////////////////////////
            bool preprocessComment(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess number constant                                    //
            //  param wfprogram : WF program to preprocess number from        //
            //  return : True if number is successfully preprocessed          //
            ////////////////////////////////////////////////////////////////////
            bool preprocessNumber(WfProgramFile& wfprogram, char digit);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess character constant                                 //
            //  param wfprogram : WF program to preprocess character from     //
            //  return : True if character is successfully preprocessed       //
            ////////////////////////////////////////////////////////////////////
            bool preprocessCharacter(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess string constant                                    //
            //  param wfprogram : WF program to preprocess string from        //
            //  return : True if string is successfully preprocessed          //
            ////////////////////////////////////////////////////////////////////
            bool preprocessString(WfProgramFile& wfprogram);

            ////////////////////////////////////////////////////////////////////
            //  Preprocess label                                              //
            //  param wfprogram : WF program to preprocess label from         //
            //  return : True if label is successfully preprocessed           //
            ////////////////////////////////////////////////////////////////////
            bool preprocessLabel(WfProgramFile& wfprogram, char type);


        private:
            char*           m_program;              // Program array
            int32_t         m_cursor;               // Program cursor

            std::unordered_map<std::string, bool>&      m_includes; // Includes
            std::unordered_map<std::string, int32_t>&   m_labels;   // Labels
    };


#endif // WFP_WFLEXER_HEADER
