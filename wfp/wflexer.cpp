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
#include "wflexer.h"


////////////////////////////////////////////////////////////////////////////////
//  WfLexer default constructor                                               //
////////////////////////////////////////////////////////////////////////////////
WfLexer::WfLexer(std::unordered_map<std::string, bool>& includes,
    std::unordered_map<std::string, int32_t>& labels) :
m_program(0),
m_cursor(0),
m_includes(includes),
m_labels(labels)
{

}

////////////////////////////////////////////////////////////////////////////////
//  WfLexer destructor                                                        //
////////////////////////////////////////////////////////////////////////////////
WfLexer::~WfLexer()
{

}


////////////////////////////////////////////////////////////////////////////////
//  WF program lexing                                                         //
//  param path : Path of the .wf program to analyze                           //
//  return : True if the .wf program is successfully analyzed                 //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::lexer(char* program, const std::string& path)
{
    // Set program pointer
    if (!program) return false;
    m_program = program;

    // Reset program cursor
    m_cursor = 0;

    // Analyze WF program
    if (!analyze(path))
    {
        return false;
    }

    // WF program successfully analyzed
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Analyze WF program                                                        //
//  param path : Path of the .wf program to analyze                           //
//  return : True if the .wf program is successfully analyzed                 //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyze(const std::string& path)
{
    // Init .wf program
    WfProgramFile wfprogram;
    wfprogram.line = 1;
    wfprogram.path = "";

    // Extract .wf program file name
    size_t i = 0;
    for (i = path.length()-1; i > 0; --i)
    {
        if ((path[i] == '/') || (path[i] == '\\'))
        {
            ++i;
            break;
        }
    }
    wfprogram.path = path.substr(i, path.length()-i);

    // Add .wf program to included file
    m_includes[wfprogram.path] = true;

    // Open .wf program
    wfprogram.file.open(path, std::ios::in | std::ios::binary);
    if (!wfprogram.file.is_open())
    {
        // Unable to read .wf program
        std::cerr << "Error : Unable to read .wf program : " <<
            wfprogram.path << '\n';
        return false;
    }

    // Analyze .wf program
    char ch = 0;
    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Analyze line count
        if (!analyzeLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Preparse program
        switch (ch)
        {
            case '`':
                // Include
                if (!analyzeInclude(wfprogram)) return false;
                break;

            case ';':
                // Comment
                if (!analyzeComment(wfprogram)) return false;
                break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                // Number
                if (!writeProgram(ch)) return false;
                if (!analyzeNumber(wfprogram, ch)) return false;
                break;

            case '\'':
                // Character constant
                if (!writeProgram(ch)) return false;
                if (!analyzeCharacter(wfprogram)) return false;
                break;

            case '"':
                // String constant
                if (!writeProgram(ch)) return false;
                if (!analyzeString(wfprogram)) return false;
                break;

            case ':': case '@': case '=': case '!': case '>': case '<':
                // Label
                if (!writeProgram(ch)) return false;
                if (!analyzeLabel(wfprogram, ch)) return false;
                break;

            default:
                // Program instruction
                if (!std::isspace(ch) && !std::isalnum(ch))
                {
                    if (!writeProgram(ch)) return false;
                }
                break;
        }
    }

    // WF program successfully analyzed
    wfprogram.file.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze line count                                                        //
//  param wfprogram : WF program to analyze line count from                   //
//  return : True if WF line count is successfully analyzed                   //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeLineCount(WfProgramFile& wfprogram, char& ch)
{
    // Increment program line counter
    switch (ch)
    {
        case '\r':
            // Carriage return
            ++wfprogram.line;
            if (!wfprogram.file.get(ch)) return false;
            if (ch == '\r') ++wfprogram.line;
            break;

        case '\n':
            // Line feed
            ++wfprogram.line;
            if (!wfprogram.file.get(ch)) return false;
            if (ch == '\n') ++wfprogram.line;
            break;

        default:
            break;
    }

    // Line count successfully analyzed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze includes                                                          //
//  param wfprogram : WF program to analyze include from                      //
//  return : True if include is successfully analyzed                         //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeInclude(WfProgramFile& wfprogram)
{
    // Parse include path
    char ch = 0;
    std::string includepath = "";
    while (wfprogram.file.get(ch))
    {
        if (ch == '`') break;
        includepath.push_back(ch);
    }

    // Extract .wf program file name
    size_t i = 0;
    for (i = includepath.length()-1; i > 0; --i)
    {
        if ((includepath[i] == '/') || (includepath[i] == '\\'))
        {
            ++i;
            break;
        }
    }
    std::string path = includepath.substr(i, includepath.length()-i);

    // Check if .wf program is already included
    std::unordered_map<std::string, bool>::const_iterator found =
        m_includes.find(path);
    if (found == m_includes.end())
    {
        // Analyze included file
        if (!analyze(includepath))
        {
            // Unable to analyze included file
            std::cerr << "Error : Unable to analyze included file : `" <<
                includepath << "`\nincluded in " << wfprogram.path <<
                " line " << wfprogram.line << '\n';
            return false;
        }
    }

    // Included file successfully analyzed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze comments                                                          //
//  param wfprogram : WF program to analyze comments from                     //
//  return : True if comment is successfully analyzed                         //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeComment(WfProgramFile& wfprogram)
{
    // Analyze comment
    int32_t line = wfprogram.line;
    char ch = 0;
    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Analyze line count
        if (!analyzeLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // End of comment
        if (ch == ';') return true;
    }

    // Unable to analyze comment
    std::cerr << "Error : Missing closing comment character ;" <<
        "\nopening comment character ; in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze number constant                                                   //
//  param wfprogram : WF program to analyze number from                       //
//  return : True if number is successfully analyzed                          //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeNumber(WfProgramFile& wfprogram, char digit)
{
    // Analyze string
    int32_t line = wfprogram.line;
    char ch = 0;
    int64_t num64 = 0;
    std::string number = "";
    int32_t base = 10;
    size_t maxsize = 10;

    // Check leading zero
    number.push_back(digit);
    if (digit == '0')
    {
        while (wfprogram.file)
        {
            // End of .wf program
            if (!wfprogram.file.get(ch)) break;

            // Analyze line count
            if (!analyzeLineCount(wfprogram, ch)) break;

            // Skip invalid program characters
            if ((ch < 32) || (ch > 126)) continue;

            if (std::isdigit(ch) ||
                (ch == 'X') || (ch == 'x') || (ch == 'B') || (ch == 'b'))
            {
                // Add current character to program
                if (!writeProgram(ch)) return false;

                // Check base
                switch (ch)
                {
                    case 'B': case 'b':
                        // Binary
                        base = 2;
                        maxsize = 32;
                        number = "";
                        break;

                    case 'X': case 'x':
                        // Hexadecimal
                        base = 16;
                        maxsize = 8;
                        number = "";
                        break;

                    default:
                        // Decimal
                        base = 10;
                        maxsize = 10;
                        number.push_back(ch);
                        break;
                }
                break;
            }
            else
            {
                // Number constant 0 succesfully parsed
                wfprogram.file.putback(ch);
                return true;
            }
        }
    }

    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Analyze line count
        if (!analyzeLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        if (std::isxdigit(ch))
        {
            // Add current character to program
            if (!writeProgram(ch)) return false;
            number.push_back(ch);
        }
        else
        {
            // End of number constant
            wfprogram.file.putback(ch);
            break;
        }
    }

    // Erase leading zeros
    number.erase(
        0, std::min(number.find_first_not_of('0'), number.size()-1)
    );

    // Check number constant range
    if (number.size() <= maxsize)
    {
        num64 = std::stoll(number, 0, base);
        if (base == 10)
        {
            if (num64 <= 0x7FFFFFFF) return true;
        }
        else
        {
            if (num64 <= 0xFFFFFFFF) return true;
        }
    }

    // Number constant out of range
    std::cerr << "Error : Number constant out of range " <<
        number << "\nin " << wfprogram.path << " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze character constant                                                //
//  param wfprogram : WF program to analyze character from                    //
//  return : True if character is successfully analyzed                       //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeCharacter(WfProgramFile& wfprogram)
{
    // Analyze character
    int32_t line = wfprogram.line;
    char ch = 0;
    int32_t i = 0;

    while (wfprogram.file && (i < 2))
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Analyze line count
        if (!analyzeLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Add current character to program
        if (!writeProgram(ch)) return false;
        ++i;

        // End of character constant
        if (ch == '\'')
        {
            // Check empty character constant
            if (i <= 1)
            {
                // Empty character constant
                std::cerr << "Error : Empty character constant ''" <<
                    "\nin " << wfprogram.path << " line " << line << '\n';
                return false;
            }

            // Character constant successfully analyzed
            return true;
        }
    }

    // Unable to analyze character constant
    std::cerr << "Error : Missing closing character constant '" <<
        "\nopening character constant ' in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze string constant                                                   //
//  param wfprogram : WF program to analyze string from                       //
//  return : True if string is successfully analyzed                          //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeString(WfProgramFile& wfprogram)
{
    // Analyze string
    int32_t line = wfprogram.line;
    char ch = 0;
    int32_t i = 0;

    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Analyze line count
        if (!analyzeLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Add current character to program
        if (!writeProgram(ch)) return false;
        ++i;

        // End of string constant
        if (ch == '\"')
        {
            // Check empty string constant
            if (i <= 1)
            {
                // Empty string constant
                std::cerr << "Error : Empty string constant \"\"" <<
                    "\nin " << wfprogram.path << " line " << line << '\n';
                return false;
            }

            // String constant successfully analyzed
            return true;
        }
    }

    // Unable to analyze string constant
    std::cerr << "Error : Missing closing string constant \"" <<
        "\nopening string constant \" in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Analyze label                                                             //
//  param wfprogram : WF program to analyze label from                        //
//  return : True if label is successfully analyzed                           //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::analyzeLabel(WfProgramFile& wfprogram, char type)
{
    // Analyze label
    int32_t line = wfprogram.line;
    char ch = 0;
    int32_t i = 0;
    std::string label = "";

    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Analyze line count
        if (!analyzeLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Add character to program
        if (!writeProgram(ch)) return false;
        ++i;

        if (ch != type)
        {
            // Add character to label
            label.push_back(ch);
        }
        else
        {
            // End of label
            if (type == ':')
            {
                // Check if label is already existing
                std::unordered_map<std::string, int32_t>::const_iterator found =
                    m_labels.find(label);
                if (found == m_labels.end())
                {
                    m_labels[label] = m_cursor;
                }
                else
                {
                    // Label is already existing
                    std::cerr << "Error : Label :" << label <<
                        ": is already defined\n" <<
                        "label redefinition in " << wfprogram.path <<
                        " line " << line << '\n';
                    return false;
                }
            }

            // Check empty label
            if (i <= 1)
            {
                // Empty label
                std::cerr << "Error : Empty label " << type << type <<
                    "\nin " << wfprogram.path << " line " << line << '\n';
                return false;
            }

            // Label successfully analyzed
            return true;
        }
    }

    // Unable to analyze label
    std::cerr << "Error : Missing closing label " << type <<
        "\nopening label " << type << " in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Write character into program                                              //
//  param ch : Character to add to the program                                //
//  return : True if the character is successfully written                    //
////////////////////////////////////////////////////////////////////////////////
bool WfLexer::writeProgram(char ch)
{
    // Write character into program memory
    if (m_cursor < WFProgramSize)
    {
        m_program[m_cursor++] = ch;
        return true;
    }

    // Unable to write character into program
    std::cerr << "Error : Program maximum allowed size exceeded\n";
    return false;
}
