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
//     wfp.cpp : WFP Main Interpreter                                         //
////////////////////////////////////////////////////////////////////////////////
#include "wfp.h"


////////////////////////////////////////////////////////////////////////////////
//  Wfp default constructor                                                   //
////////////////////////////////////////////////////////////////////////////////
Wfp::Wfp() :
m_program(0),
m_cursor(0),
m_memory(0),
m_pointer(0),
m_backpointer(0),
m_register(0),
m_backregister(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  Wfp destructor                                                            //
////////////////////////////////////////////////////////////////////////////////
Wfp::~Wfp()
{
    if (m_memory) { delete[] m_memory; }
    m_memory = 0;
    if (m_program) { delete[] m_program; }
    m_program = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Launch WFP                                                                //
//  param path : Path of the .wf program to run                               //
//  return : True if WFP successfully started, false otherwise                //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::launch(const std::string& path)
{
    // Reset program array
    if (m_program) { delete[] m_program; }
    m_program = 0;

    // Init program array
    try
    {
        m_program = new char[WFProgramSize+WFProgramOverhead];
    }
    catch (std::bad_alloc&)
    {
        m_program = 0;
    }
    catch (...)
    {
        m_program = 0;
    }

    // Check program array
    if (!m_program)
    {
        // Invalid program array
        std::cerr << "Error : Unable to initialize program array\n";
        return false;
    }

    // Reset program array
    memset(m_program, 0, sizeof(char)*(WFProgramSize+WFProgramOverhead));

    // Reset memory array
    if (m_memory) { delete[] m_memory; }
    m_memory = 0;

    // Init memory array
    try
    {
        m_memory = new int32_t[WFMemorySize];
    }
    catch (std::bad_alloc&)
    {
        m_memory = 0;
    }
    catch (...)
    {
        m_memory = 0;
    }

    // Check memory array
    if (!m_memory)
    {
        // Invalid memory array
        std::cerr << "Error : Unable to initialize memory array\n";
        return false;
    }

    // Reset memory array
    memset(m_memory, 0, sizeof(int32_t)*WFMemorySize);

    // Preprocess .wf program
    m_cursor = 0;
    if (!preprocess(path))
    {
        // Unable to read .wf program
        return false;
    }

    // Reset WFP states
    m_cursor = 0;
    m_pointer = &m_memory[WFMemoryOffset];
    m_backpointer = &m_memory[WFMemoryOffset];
    m_register = 0;
    m_backregister = 0;

    // Run WFP
    run();

    // End of program
    if (WFMemoryDump)
    {
        // Output memory dump
        std::cout << "\n----------------------------------------\n";
        std::cout << "Memory : [-20 to +19]" << '\n';
        for (int32_t i = WFMemoryOffset-20; i < WFMemoryOffset+20; ++i)
        {
            if (i == WFMemoryOffset) std::cout << '\n';
            std::cout << m_memory[i] << ' ';
        }
        std::cout << '\n' << "Reg : " << m_register;
        std::cout << " | Back Reg : " << m_backregister << '\n';
        std::cout << "Ptr : " << (m_pointer-&m_memory[WFMemoryOffset]);
        std::cout << " | Back Ptr : " <<
            (m_backpointer-&m_memory[WFMemoryOffset]) << '\n';
        std::cout << "Cursor : " << m_cursor << '\n';
        std::cout << "----------------------------------------\n";
    }

    // WFP successfully terminated
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Preprocess WF program                                                     //
//  param path : Path of the .wf program to preprocess                        //
//  return : True if the .wf program is successfully preprocessed             //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocess(const std::string& path)
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

    // Preprocess .wf program
    char ch = 0;
    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Preprocess line count
        if (!preprocessLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Preparse program
        switch (ch)
        {
            case ';':
                // Comment
                if (!preprocessComment(wfprogram)) return false;
                break;

            case '`':
                // Include
                if (!preprocessInclude(wfprogram)) return false;
                break;

            case ':': case '@': case '=': case '!': case '>': case '<':
                // Label
                m_program[m_cursor++] = ch;
                if (!preprocessLabel(wfprogram, ch)) return false;
                break;

            case '\'':
                // Character constant
                m_program[m_cursor++] = ch;
                if (!preprocessCharacter(wfprogram)) return false;
                break;

            case '"':
                // String constant
                m_program[m_cursor++] = ch;
                if (!preprocessString(wfprogram)) return false;
                break;

            default:
                // Program instruction
                if (!std::isspace(ch) && !std::isalnum(ch))
                {
                    m_program[m_cursor++] = ch;
                }
                break;
        }
    }

    wfprogram.file.close();
}

////////////////////////////////////////////////////////////////////////////////
//  Run WFP                                                                   //
////////////////////////////////////////////////////////////////////////////////
void Wfp::run()
{
    // WF Parser
    for (m_cursor = 0; m_cursor < WFProgramSize; ++m_cursor)
    {
        // End of program
        if (m_program[m_cursor] == 0) break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Preprocess line count                                                     //
//  param wfprogram : WF program to preprocess line count from                //
//  return : True if WF line count is successfully preprocessed               //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocessLineCount(WfProgramFile& wfprogram, char& ch)
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

    // Line count successfully preprocessed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Preprocess comments                                                       //
//  param wfprogram : WF program to preprocess comments from                  //
//  return : True if comment is successfully preprocessed                     //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocessComment(WfProgramFile& wfprogram)
{
    // Preprocess comment
    int32_t line = wfprogram.line;
    char ch = 0;
    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Preprocess line count
        if (!preprocessLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // End of comment
        if (ch == ';') return true;
    }

    // Unable to preprocess comment
    std::cerr << "Error : Missing closing comment character ;" <<
        "\nopening comment character ; in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Preprocess includes                                                       //
//  param wfprogram : WF program to preprocess include from                   //
//  return : True if include is successfully preprocessed                     //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocessInclude(WfProgramFile& wfprogram)
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
        // Preprocess included file
        if (!preprocess(includepath))
        {
            // Unable to preprocess included file
            std::cerr << "Error : Unable to preprocess included file : `" <<
                includepath << "`\nincluded in " << wfprogram.path <<
                " line " << wfprogram.line << '\n';
            return false;
        }
    }

    // Included file successfully preprocessed
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Preprocess label                                                          //
//  param wfprogram : WF program to preprocess label from                     //
//  return : True if label is successfully preprocessed                       //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocessLabel(WfProgramFile& wfprogram, char type)
{
    // Preprocess label
    int32_t line = wfprogram.line;
    char ch = 0;
    std::string label = "";

    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Preprocess line count
        if (!preprocessLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        if (ch != type)
        {
            // Add character to label
            label.push_back(ch);

            // Add character tro program
            m_program[m_cursor++] = ch;
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

            // Label successfully preprocessed
            return true;
        }
    }

    // Unable to preprocess label
    std::cerr << "Error : Missing closing label " << type <<
        "\nopening label " << type << " in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Preprocess character constant                                             //
//  param wfprogram : WF program to preprocess character from                 //
//  return : True if character is successfully preprocessed                   //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocessCharacter(WfProgramFile& wfprogram)
{
    // Preprocess character
    int32_t line = wfprogram.line;
    char ch = 0;
    int32_t i = 0;
    while (wfprogram.file && (i < 2))
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Preprocess line count
        if (!preprocessLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Add current character to program
        m_program[m_cursor++] = ch;
        ++i;

        // End of string
        if (ch == '\'')
        {
            if (i <= 1)
            {
                // Empty character constant
                std::cerr << "Error : Empty character constant ''" <<
                    "\nin " << wfprogram.path << " line " << line << '\n';
                return false;
            }
            return true;
        }
    }

    // Unable to preprocess string
    std::cerr << "Error : Missing closing character constant '" <<
        "\nopening character constant ' in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Preprocess string constant                                                //
//  param wfprogram : WF program to preprocess string from                    //
//  return : True if string is successfully preprocessed                      //
////////////////////////////////////////////////////////////////////////////////
bool Wfp::preprocessString(WfProgramFile& wfprogram)
{
    // Preprocess string
    int32_t line = wfprogram.line;
    char ch = 0;
    int32_t i = 0;
    while (wfprogram.file)
    {
        // End of .wf program
        if (!wfprogram.file.get(ch)) break;

        // Preprocess line count
        if (!preprocessLineCount(wfprogram, ch)) break;

        // Skip invalid program characters
        if ((ch < 32) || (ch > 126)) continue;

        // Add current character to program
        m_program[m_cursor++] = ch;
        ++i;

        // End of string
        if (ch == '\"')
        {
            if (i <= 1)
            {
                // Empty string constant
                std::cerr << "Error : Empty string constant \"\"" <<
                    "\nin " << wfprogram.path << " line " << line << '\n';
                return false;
            }
            return true;
        }
    }

    // Unable to preprocess string
    std::cerr << "Error : Missing closing string constant \"" <<
        "\nopening string constant \" in " << wfprogram.path <<
        " line " << line << '\n';
    return false;
}
