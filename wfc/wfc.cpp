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
//     wfc.cpp : WFC Main Interpreter                                         //
////////////////////////////////////////////////////////////////////////////////
#include "wfc.h"


////////////////////////////////////////////////////////////////////////////////
//  Wfc default constructor                                                   //
////////////////////////////////////////////////////////////////////////////////
Wfc::Wfc() :
m_program(0),
m_cursor(0),
m_includes(),
m_labels(),
m_wflexer(m_includes, m_labels),
m_output()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Wfc destructor                                                            //
////////////////////////////////////////////////////////////////////////////////
Wfc::~Wfc()
{
    if (m_program) { delete[] m_program; }
    m_program = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Launch WFC                                                                //
//  param path : Path of the .wf program to run                               //
//  return : True if WFC successfully started, false otherwise                //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::launch(const std::string& path)
{
    // Extract .wf program file name
    std::string asmpath = "";
    size_t i = 0;
    for (i = path.length()-1; i > 0; --i)
    {
        if ((path[i] == '/') || (path[i] == '\\'))
        {
            ++i;
            break;
        }
    }
    asmpath = path.substr(i, path.length()-i);

    // Remove file extension
    for (i = 0; i < asmpath.length(); ++i)
    {
        if (asmpath[i] == '.')
        {
            ++i;
            break;
        }
    }
    asmpath = asmpath.substr(0, i-1);

    // Add .asm extension
    asmpath += ".asm";

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

    // Preprocess .wf program
    m_cursor = 0;
    if (!m_wflexer.lexer(m_program, path))
    {
        // Unable to read .wf program
        return false;
    }

    // Reset WFC states
    m_cursor = 0;
    if (m_output.is_open()) m_output.close();
    m_output.open(asmpath, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!m_output.is_open())
    {
        // Unable to open output assembly file
        std::cerr <<
            "Error : Unable to open output assembly file : " << asmpath << "\n";
        return false;
    }

    // Set stream format to hexadecimal
    m_output << std::hex;

    // Run WFC
    if (!run()) return false;

    // WFC successfully terminated
    if (m_output.is_open()) m_output.close();
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Run WFC                                                                   //
//  return : True if WF is successfully compiled, false otherwise             //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::run()
{
    // WF header
    if (!writeHeader()) return false;

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

    // WF footer
    if (!writeFooter()) return false;

    // WF successfully compiled
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Parse number constant                                                     //
////////////////////////////////////////////////////////////////////////////////
void Wfc::parseNumber()
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
    num64 = std::stoll(number, 0, base);
    writeNumber(num64);
}

////////////////////////////////////////////////////////////////////////////////
//  Parse character constant                                                  //
////////////////////////////////////////////////////////////////////////////////
void Wfc::parseCharacter()
{
    // Parse character
    writeCharacter(m_program[(++m_cursor)++]);
}

////////////////////////////////////////////////////////////////////////////////
//  Parse string constant                                                     //
////////////////////////////////////////////////////////////////////////////////
void Wfc::parseString()
{
    // Parse string
    std::string str = "";
    ++m_cursor;
    while (m_program[m_cursor] != '"')
    {
        str.push_back(m_program[m_cursor++]);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Parse label                                                               //
////////////////////////////////////////////////////////////////////////////////
void Wfc::parseLabel()
{
    // Parse label
    std::string label = "";
    char type = m_program[m_cursor++];
    while (m_program[m_cursor] != type)
    {
        label.push_back(m_program[m_cursor++]);
    }

    // Jump to label
    switch (type)
    {
        case ':':
            writeLabel(label);
            break;

        case '@':
            writeJump(label);
            break;

        case '$':
            writeCall(label);
            break;

        case '=':
            writeJumpEZ(label);
            break;

        case '!':
            writeJumpNZ(label);
            break;

        case '>':
            writeJumpGZ(label);
            break;

        case '<':
            writeJumpLZ(label);
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Parse instruction                                                         //
////////////////////////////////////////////////////////////////////////////////
void Wfc::parseInstruction()
{
    int32_t tmp = 0;
    switch (m_program[m_cursor])
    {
        case '\\':
            // Swap pointers
            writeSwapPointers();
            break;

        case '}':
            // Increment pointer
            writeIncrementPointer();
            break;

        case '{':
            // Decrement pointer
            writeDecrementPointer();
            break;

        case ']':
            // Set current pointer address
            writeSetPointerAddress();
            break;

        case '[':
            // Load current pointer address
            writeGetPointerAddress();
            break;


        case '~':
            // Swap register
            writeSwapRegisters();
            break;

        case '#':
            // Load current pointed value
            writeLoadPointedValue();
            break;

        case '_':
            // Store current register value
            writeStoreRegisterValue();
            break;

        case '^':
            // Jump back to caller
            break;


        case '+':
            // Add
            writeAddRegisters();
            break;

        case '-':
            // Subtract
            writeSubtractRegisters();
            break;

        case '*':
            // Multiply
            writeMultiplyRegisters();
            break;

        case '/':
            // Divide
            writeDivideRegisters();
            break;

        case '%':
            // Modulo
            writeModuloRegisters();
            break;

        case '&':
            // Bitwise AND
            break;

        case '|':
            // Bitwise OR
            break;


        case ',':
            // Read input byte
            break;

        case '.':
            // Write output byte
            writeOutput();
            break;

        case ')':
            // Set I/O cursor position
            break;

        case '(':
            // Load I/O cursor position
            break;

        case '?':
            // Set I/O mode
            break;

        default:
            // Invalid instruction
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF header                                                           //
//  return : True if WF header is successfully written                        //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeHeader()
{
    m_output << WFASMHeader;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF footer                                                           //
//  return : True if WF footer is successfully written                        //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeFooter()
{
    m_output << WFASMFooter;
    return (!m_output.bad());
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF number                                                           //
//  return : True if WF number is successfully written                        //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeNumber(int64_t num)
{
    m_output << WFASMNumberHead << num << WFASMNumberFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF character                                                        //
//  return : True if WF character is successfully written                     //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeCharacter(char ch)
{
    m_output << WFASMCharacterHead << ch << WFASMCharacterFoot;
    return (!m_output.bad());
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF label                                                            //
//  return : True if WF label is successfully written                         //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeLabel(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMLabelHead << labelNum << WFASMLabelFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF jump                                                             //
//  return : True if WF jump is successfully written                          //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeJump(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMJumpHead << labelNum << WFASMJumpFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF call                                                             //
//  return : True if WF call is successfully written                          //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeCall(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMCallHead << labelNum << WFASMCallFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF jump equal to zero                                               //
//  return : True if WF jump EZ is successfully written                       //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeJumpEZ(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMJumpEZHead << labelNum << WFASMJumpEZFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF jump not equal to zero                                           //
//  return : True if WF jump NZ is successfully written                       //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeJumpNZ(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMJumpNZHead << labelNum << WFASMJumpNZFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF jump greater than zero                                           //
//  return : True if WF jump GZ is successfully written                       //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeJumpGZ(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMJumpGZHead << labelNum << WFASMJumpGZFoot;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF jump less than zero                                              //
//  return : True if WF jump LZ is successfully written                       //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeJumpLZ(const std::string& label)
{
    int32_t labelNum = m_labels[label];
    m_output << WFASMJumpLZHead << labelNum << WFASMJumpLZFoot;
    return (!m_output.bad());
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF swap pointers                                                    //
//  return : True if WF swap pointers is successfully written                 //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeSwapPointers()
{
    m_output << WFASMSwapPointers;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF increment pointer                                                //
//  return : True if WF inc pointer is successfully written                   //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeIncrementPointer()
{
    m_output << WFASMIncrementPointer;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF decrement pointer                                                //
//  return : True if WF dec pointer is successfully written                   //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeDecrementPointer()
{
    m_output << WFASMDecrementPointer;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF set pointer address                                              //
//  return : True if WF set pointer is successfully written                   //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeSetPointerAddress()
{
    m_output << WFASMSetPointerAddress;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF get pointer address                                              //
//  return : True if WF get pointer is successfully written                   //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeGetPointerAddress()
{
    m_output << WFASMGetPointerAddress;
    return (!m_output.bad());
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF swap registers                                                   //
//  return : True if WF swap registers is successfully written                //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeSwapRegisters()
{
    m_output << WFASMSwapRegisters;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF load pointed value                                               //
//  return : True if WF load value is successfully written                    //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeLoadPointedValue()
{
    m_output << WFASMLoadPointedValue;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF store register value                                             //
//  return : True if WF store value is successfully written                   //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeStoreRegisterValue()
{
    m_output << WFASMStoreRegisterValue;
    return (!m_output.bad());
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF add registers                                                    //
//  return : True if WF add is successfully written                           //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeAddRegisters()
{
    m_output << WFASMAddRegisters;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF subtract registers                                               //
//  return : True if WF subtract is successfully written                      //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeSubtractRegisters()
{
    m_output << WFASMSubtractRegisters;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF multiply registers                                               //
//  return : True if WF multiply is successfully written                      //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeMultiplyRegisters()
{
    m_output << WFASMMultiplyRegisters;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF divide registers                                                 //
//  return : True if WF divide is successfully written                        //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeDivideRegisters()
{
    m_output << WFASMDivideRegisters;
    return (!m_output.bad());
}

////////////////////////////////////////////////////////////////////////////////
//  Write WF modulo registers                                                 //
//  return : True if WF modulo is successfully written                        //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeModuloRegisters()
{
    m_output << WFASMModuloRegisters;
    return (!m_output.bad());
}


////////////////////////////////////////////////////////////////////////////////
//  Write WF output                                                           //
//  return : True if WF output is successfully written                        //
////////////////////////////////////////////////////////////////////////////////
bool Wfc::writeOutput()
{
    m_output << WFASMStandardOutput;
    return (!m_output.bad());
}
