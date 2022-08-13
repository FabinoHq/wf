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
m_backregister(0),
m_includes(),
m_labels(),
m_wflexer(m_includes, m_labels)
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
    if (!m_wflexer.lexer(m_program, path))
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
//  Run WFP                                                                   //
////////////////////////////////////////////////////////////////////////////////
void Wfp::run()
{
    // WF Parser
    for (m_cursor = 0; m_cursor < WFProgramSize; ++m_cursor)
    {
        // End of program
        if (m_program[m_cursor] == 0) break;

        switch (m_program[m_cursor])
        {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                // Number constant
                parseNumber();
                break;

            case '\'':
                // Character constant
                parseCharacter();
                break;

            case '"':
                // String constant
                parseString();
                break;

            default:
                // Invalid instruction
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Parse number constant                                                     //
////////////////////////////////////////////////////////////////////////////////
void Wfp::parseNumber()
{
    std::string number = "";
    int64_t num64 = 0;
    int32_t base = 10;

    // Check leading 0
    if ((m_program[m_cursor+1] == 'B') || (m_program[m_cursor+1] == 'b'))
    {
        // Binary number constant
        m_cursor += 2;
        base = 2;
    }
    if ((m_program[m_cursor+1] == 'X') || (m_program[m_cursor+1] == 'x'))
    {
        // Hexadecimal number constant
        m_cursor += 2;
        base = 16;
    }
    else
    {
        // Decimal number constant
        base = 10;
    }

    // Parse number
    while (std::isxdigit(m_program[m_cursor]))
    {
        number.push_back(m_program[m_cursor++]);
    }
    num64 = std::stoll(number, 0, base);
    m_register = static_cast<int32_t>(num64);
}

////////////////////////////////////////////////////////////////////////////////
//  Parse character constant                                                  //
////////////////////////////////////////////////////////////////////////////////
void Wfp::parseCharacter()
{
    // Parse character
    m_register = m_program[(++m_cursor)++];
}

////////////////////////////////////////////////////////////////////////////////
//  Parse string constant                                                     //
////////////////////////////////////////////////////////////////////////////////
void Wfp::parseString()
{
    // Parse string
    int32_t* pointer = m_pointer;
    ++m_cursor;
    while (m_program[m_cursor] != '"')
    {
        *(m_pointer++) = m_program[m_cursor++];
    }
    m_pointer = pointer;
}
