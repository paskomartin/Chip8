#include "chip8.h"
#include "chip8internaldata.h"
#include "chip8opcodedata.h"
#include "instruction.h"
#include "instructionset.h"

namespace Chip8
{
  Chip8::Chip8()
  {
    data.reset( new Chip8InternalData );
    instructions.reset( new InstructionSet );
  }

  void Chip8::execute()
  {
    // fetch opcode
    struct Chip8OpcodeData op;
    op.opcode = fetchOpcode();

    increasePC();
    decodeOpcode(op);
    executeOpcode(op);
  }

  unsigned short Chip8::fetchOpcode()
  {
    auto *mem = data->memory.data();
    auto PC = data->PC;

    unsigned short opcode = ( ( mem[PC & 0xFFF]) << 8 ) | ( mem[(PC + 1) & 0xFFF]);
    return opcode;
  }

  void Chip8::decodeOpcode(Chip8OpcodeData &op)
  {
    unsigned short opcode = op.opcode;
    op.funcNum = ( opcode >> 12 ) && 0xF;
    op.subFuncNum = opcode && 0xF;
    op.n = op.subFuncNum;
    op.nnn = opcode & 0xFFF;
    op.kk = opcode & 0xFF;
    op.x = (opcode >> 8) & 0xf;
    op.y = (opcode >> 4) & 0xf;
  }

  void Chip8::executeOpcode(Chip8OpcodeData &opcode)
  {

  }

  void Chip8::increasePC(unsigned int counter)
  {
    data->PC += counter;
  }

  void Chip8::setCarryFlag()
  {
    *(data->carryReg) = 1;
  }

  void Chip8::unsetCarryFlag()
  {
    *(data->carryReg) = 0;
  }

}
