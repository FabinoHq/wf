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
m_stack(),
m_memory(0),
m_pointer(0),
m_backpointer(0),
m_register(0),
m_backregister(0),
m_curInputFile(""),
m_curOutputFile(""),
m_inputFile(),
m_outputFile(),
m_rwFile(),
m_iomode(WF_IOMODE_STANDARD),
m_iofile(WF_IOFILE_IO),
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
    m_pointer = 0;
    m_backpointer = 0;
    m_register = 0;
    m_backregister = 0;
    m_curInputFile = "";
    m_curOutputFile = "";
    if (m_inputFile.is_open()) m_inputFile.close();
    if (m_outputFile.is_open()) m_outputFile.close();
    if (m_rwFile.is_open()) m_rwFile.close();

    // Run WFP
    run();

    // Close opened files
    m_curInputFile = "";
    m_curOutputFile = "";
    if (m_inputFile.is_open()) m_inputFile.close();
    if (m_outputFile.is_open()) m_outputFile.close();
    if (m_rwFile.is_open()) m_rwFile.close();

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
        std::cout << "Ptr : " << m_pointer;
        std::cout << " | Back Ptr : " << m_backpointer << '\n';
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

            case ':': case '@': case '$':
            case '=': case '!': case '>': case '<':
                // Label and jump to label
                parseLabel();
                break;

            default:
                // Program instruction
                parseInstruction();
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
    else if ((m_program[m_cursor+1] == 'X') || (m_program[m_cursor+1] == 'x'))
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
    --m_cursor;
    try { num64 = std::stoll(number, 0, base); }
    catch (...) { num64 = 0; }
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
    int32_t pointer = m_pointer;
    ++m_cursor;
    while (m_program[m_cursor] != '"')
    {
        checkPointerAddress();
        m_memory[(m_pointer++)+WFMemoryOffset] = m_program[m_cursor++];
    }
    checkPointerAddress();
    m_memory[(m_pointer++)+WFMemoryOffset] = 0;
    m_pointer = pointer;
}

////////////////////////////////////////////////////////////////////////////////
//  Parse label                                                               //
////////////////////////////////////////////////////////////////////////////////
void Wfp::parseLabel()
{
    // Parse label
    std::string label = "";
    char type = m_program[m_cursor++];
    int32_t cursor = m_cursor;
    while (m_program[m_cursor] != type)
    {
        label.push_back(m_program[m_cursor++]);
    }

    // Jump to label
    switch (type)
    {
        case '@':
            m_cursor = m_labels[label]-1;
            break;

        case '$':
            cursor = m_cursor;
            m_cursor = m_labels[label]-1;
            m_stack.push(cursor);
            break;

        case '=':
            if (m_register == 0) m_cursor = m_labels[label]-1;
            break;

        case '!':
            if (m_register != 0) m_cursor = m_labels[label]-1;
            break;

        case '>':
            if (m_register > 0) m_cursor = m_labels[label]-1;
            break;

        case '<':
            if (m_register < 0) m_cursor = m_labels[label]-1;
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Parse instruction                                                         //
////////////////////////////////////////////////////////////////////////////////
void Wfp::parseInstruction()
{
    int32_t tmp = 0;
    switch (m_program[m_cursor])
    {
        case '\\':
            // Swap pointers
            tmp = m_pointer;
            m_pointer = m_backpointer;
            m_backpointer = tmp;
            break;

        case '}':
            // Increment pointer
            ++m_pointer;
            break;

        case '{':
            // Decrement pointer
            --m_pointer;
            break;

        case ']':
            // Set current pointer address
            m_pointer = m_register;
            break;

        case '[':
            // Load current pointer address
            m_register = m_pointer;
            break;


        case '~':
            // Swap register
            tmp = m_register;
            m_register = m_backregister;
            m_backregister = tmp;
            break;

        case '#':
            // Load current pointed value
            checkPointerAddress();
            m_register = m_memory[m_pointer+WFMemoryOffset];
            break;

        case '_':
            // Store current register value
            checkPointerAddress();
            m_memory[m_pointer+WFMemoryOffset] = m_register;
            break;

        case '^':
            // Jump back to caller
            if (!m_stack.empty())
            {
                // Function return
                m_cursor = m_stack.top();
                m_stack.pop();
            }
            else
            {
                // Program return
                m_cursor = WFProgramSize;
            }
            break;


        case '+':
            // Add
            m_register = (m_register + m_backregister);
            break;

        case '-':
            // Subtract
            m_register = (m_register - m_backregister);
            break;

        case '*':
            // Multiply
            m_register = (m_register * m_backregister);
            break;

        case '/':
            // Divide
            if (m_backregister != 0)
            {
                m_register = (m_register / m_backregister);
            }
            else
            {
                m_register = 0;
            }
            break;

        case '%':
            // Modulo
            if (m_backregister != 0)
            {
                m_register = (m_register % m_backregister);
            }
            else
            {
                m_register = 0;
            }
            break;

        case '&':
            // Bitwise AND
            m_register = (m_register & m_backregister);
            break;

        case '|':
            // Bitwise OR
            m_register = (m_register | m_backregister);
            break;


        case ',':
            // Read input byte
            readInput();
            break;

        case '.':
            // Write output byte
            writeOutput();
            break;

        case ')':
            // Set I/O cursor position
            setIOCursorPosition();
            break;

        case '(':
            // Load I/O cursor position
            getIOCursorPosition();
            break;

        case '?':
            // Set I/O mode
            setIOMode();
            break;

        default:
            // Invalid instruction
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Read input byte                                                           //
////////////////////////////////////////////////////////////////////////////////
void Wfp::readInput()
{
    char ch = 0;
    switch (m_iomode)
    {
        case WF_IOMODE_FILE_INPUT:
            // File input
            m_register = -1;
            if (m_iofile == WF_IOFILE_IO)
            {
                if (m_inputFile.is_open())
                {
                    if (m_inputFile.read(&ch, 1))
                    {
                        m_register = ch;
                    }
                }
            }
            else
            {
                if (m_rwFile.is_open())
                {
                    if (m_rwFile.read(&ch, 1))
                    {
                        m_register = ch;
                    }
                }
            }
            break;

        case WF_IOMODE_FILE_OUTPUT:
            // File output
            break;

        default:
            // Standard input
            m_register = WFKeyboardInput();
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Write output byte                                                         //
////////////////////////////////////////////////////////////////////////////////
void Wfp::writeOutput()
{
    char ch = static_cast<char>(m_register);
    switch (m_iomode)
    {
        case WF_IOMODE_FILE_INPUT:
            // File input
            break;

        case WF_IOMODE_FILE_OUTPUT:
            // File output
            if (m_iofile == WF_IOFILE_IO)
            {
                if (m_outputFile.is_open())
                {
                    m_outputFile.write(&ch, 1);
                }
            }
            else
            {
                if (m_rwFile.is_open())
                {
                    m_rwFile.write(&ch, 1);
                }
            }
            break;

        default:
            // Standard output
            std::cout << ch;
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set I/O cursor position                                                   //
////////////////////////////////////////////////////////////////////////////////
void Wfp::setIOCursorPosition()
{
    // Set I/O cursor position
    switch (m_iomode)
    {
        case WF_IOMODE_FILE_INPUT:
            // File input
            if (m_iofile == WF_IOFILE_IO)
            {
                if (m_inputFile.is_open())
                {
                    m_inputFile.seekg(m_register, std::ios::beg);
                }
            }
            else
            {
                if (m_rwFile.is_open())
                {
                    m_rwFile.seekp(m_register, std::ios::beg);
                }
            }
            break;

        case WF_IOMODE_FILE_OUTPUT:
            // File output
            if (m_iofile == WF_IOFILE_IO)
            {
                if (m_outputFile.is_open())
                {
                    m_outputFile.seekp(m_register, std::ios::beg);
                }
            }
            else
            {
                if (m_rwFile.is_open())
                {
                    m_rwFile.seekp(m_register, std::ios::beg);
                }
            }
            break;

        default:
            // Standard I/O
            WFSetTerminalCursor(m_register, m_backregister);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Get I/O cursor position                                                   //
////////////////////////////////////////////////////////////////////////////////
void Wfp::getIOCursorPosition()
{
    // Get I/O cursor position
    switch (m_iomode)
    {
        case WF_IOMODE_FILE_INPUT:
            // File input
            if (m_iofile == WF_IOFILE_IO)
            {
                if (m_inputFile.is_open())
                {
                    m_register = static_cast<int32_t>(m_inputFile.tellg());
                }
            }
            else
            {
                if (m_rwFile.is_open())
                {
                    m_register = static_cast<int32_t>(m_rwFile.tellp());
                }
            }
            break;

        case WF_IOMODE_FILE_OUTPUT:
            // File output
            if (m_iofile == WF_IOFILE_IO)
            {
                if (m_outputFile.is_open())
                {
                    m_register = static_cast<int32_t>(m_outputFile.tellp());
                }
            }
            else
            {
                if (m_rwFile.is_open())
                {
                    m_register = static_cast<int32_t>(m_rwFile.tellp());
                }
            }
            break;

        default:
            // Standard I/O
            WFGetTerminalCursor(m_register, m_backregister);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Set I/O mode                                                              //
////////////////////////////////////////////////////////////////////////////////
void Wfp::setIOMode()
{
    // Set I/O mode
    int32_t pointer = m_pointer;
    std::string path = "";
    switch (m_register)
    {
        case 'r':
            // Open input file mode
            m_register = -1;
            m_iomode = WF_IOMODE_FILE_INPUT;
            m_iofile = WF_IOFILE_IO;

            // Close previous input files
            m_curInputFile = "";
            if (m_inputFile.is_open()) m_inputFile.close();
            if (m_rwFile.is_open()) m_rwFile.close();

            // Read file path
            checkPointerAddress();
            if (m_memory[m_pointer+WFMemoryOffset] == 0)
            {
                break;
            }
            while ((m_memory[m_pointer+WFMemoryOffset]))
            {
                path.push_back(m_memory[(m_pointer++)+WFMemoryOffset]);
                checkPointerAddress();
            }

            // Check if file is already opened in output mode
            if (path == m_curOutputFile)
            {
                break;
            }

            // Open input file
            m_inputFile.open(path, std::ios::in | std::ios::binary);
            if (m_inputFile.is_open())
            {
                m_curInputFile = path;
                m_inputFile.seekg(0, std::ios::beg);
                m_register = 0;
            }
            break;

        case 'w':
            // Open output file mode
            m_register = -1;
            m_iomode = WF_IOMODE_FILE_OUTPUT;
            m_iofile = WF_IOFILE_IO;

            // Close previous output files
            m_curOutputFile = "";
            if (m_outputFile.is_open()) m_outputFile.close();
            if (m_rwFile.is_open()) m_rwFile.close();

            // Read file path
            checkPointerAddress();
            if (m_memory[m_pointer+WFMemoryOffset] == 0)
            {
                break;
            }
            while ((m_memory[m_pointer+WFMemoryOffset]))
            {
                path.push_back(m_memory[(m_pointer++)+WFMemoryOffset]);
                checkPointerAddress();
            }

            // Check if file is already opened in input mode
            if (path == m_curInputFile)
            {
                break;
            }

            // Open output file
            m_outputFile.open(
                path, std::ios::in | std::ios::trunc | std::ios::binary
            );
            if (m_outputFile.is_open())
            {
                m_curOutputFile = path;
                m_outputFile.seekp(0, std::ios::beg);
                m_register = 0;
            }
            break;

        case 'b':
            // Open R/W file mode
            m_register = -1;
            m_iomode = WF_IOMODE_FILE_OUTPUT;
            m_iofile = WF_IOFILE_RW;

            // Close previous files
            if (m_inputFile.is_open()) m_inputFile.close();
            if (m_outputFile.is_open()) m_outputFile.close();
            if (m_rwFile.is_open()) m_rwFile.close();

            // Read file path
            checkPointerAddress();
            if (m_memory[m_pointer+WFMemoryOffset] == 0)
            {
                break;
            }
            while ((m_memory[m_pointer+WFMemoryOffset]))
            {
                path.push_back(m_memory[(m_pointer++)+WFMemoryOffset]);
                checkPointerAddress();
            }

            // Open R/W file
            m_rwFile.open(
                path, std::ios::in | std::ios::out | std::ios::binary
            );
            if (m_rwFile.is_open())
            {
                m_rwFile.seekp(0, std::ios::beg);
                m_register = 0;
            }
            break;

        case 'a':
            // Open R/W file append mode
            m_register = -1;
            m_iomode = WF_IOMODE_FILE_OUTPUT;
            m_iofile = WF_IOFILE_RW;

            // Close previous files
            if (m_inputFile.is_open()) m_inputFile.close();
            if (m_outputFile.is_open()) m_outputFile.close();
            if (m_rwFile.is_open()) m_rwFile.close();

            // Read file path
            checkPointerAddress();
            if (m_memory[m_pointer+WFMemoryOffset] == 0)
            {
                break;
            }
            while ((m_memory[m_pointer+WFMemoryOffset]))
            {
                path.push_back(m_memory[(m_pointer++)+WFMemoryOffset]);
                checkPointerAddress();
            }

            // Open R/W file
            m_rwFile.open(
                path, std::ios::in | std::ios::out |
                std::ios::binary | std::ios::app
            );
            if (m_rwFile.is_open())
            {
                m_rwFile.seekp(0, std::ios::end);
                m_register = 0;
            }
            break;

        case 'i':
            // Read input file mode
            m_iomode = WF_IOMODE_FILE_INPUT;
            break;

        case 'o':
            // Write output file mode
            m_iomode = WF_IOMODE_FILE_OUTPUT;
            break;

        default:
            // Standard I/O
            m_iomode = WF_IOMODE_STANDARD;
            break;
    }
    m_pointer = pointer;
}

////////////////////////////////////////////////////////////////////////////////
//  Check pointer address                                                     //
////////////////////////////////////////////////////////////////////////////////
void Wfp::checkPointerAddress()
{
    // Check pointer address
    if ((m_pointer < -WFMemoryOffset) || (m_pointer >= WFMemoryOffset))
    {
        // Pointer out of range
        std::cerr << "Runtime Error : Pointer out of range : " <<
            m_pointer << "\n";
        m_cursor = WFProgramSize;
    }
}
