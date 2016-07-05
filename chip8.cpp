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

  // TODO: To implement later
  void Chip8::executeOpcode(Chip8OpcodeData &op)
  {
    unsigned int funcNum = 0;
    if (op.funcNum == 0)
    {
      funcNum = op.opcode;
    }
    else if (op.funcNum > 0 && op.funcNum < 8)
    {
      funcNum = op.funcNum;
      if (op.funcNum == 5)
      {
        funcNum = 0x50;
      }
    }
    else if ( (op.funcNum == 8) | (op.funcNum == 9) )
    {
      funcNum = (op.funcNum << 8) | op.subFuncNum;
    }
    else if ( (op.funcNum >= 0xA) | (op.funcNum < 0xE) )
    {
      funcNum = op.funcNum;
    }
    else if (op.funcNum == 0xE || op.funcNum == 0xF)
    {
      funcNum = (op.funcNum << 24) | (op.kk);
    }
    else
    {
      funcNum = 0xFFFF;
    }

    Instruction *instr = instructions->GetInstruction(funcNum);
    instr->execute(data, op);
  }

  void Chip8::increasePC(unsigned int counter)
  {
    data->AdvancePC(counter);
    //data->PC += counter;
  }

  void Chip8::setCarryFlag()
  {
    data->SetCarry(1);
    //*(data->carryReg) = 1;
  }

  void Chip8::unsetCarryFlag()
  {
    data->SetCarry(0);
    //*(data->carryReg) = 0;
  }

}
