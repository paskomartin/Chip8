#include "instructionset.h"
#include "instruction.h"

namespace Chip8
{

  InstructionSet::InstructionSet()
  {
    init();
  }

  InstructionSet::~InstructionSet()
  {
    clear();
  }

  Instruction *InstructionSet::GetInstruction(int num)
  {
    // TODO: Implement this
  }

  void InstructionSet::init()
  {
    Instruction *inst = nullptr;
    int funcNum = 0;

    inst = new XOR;
    commands[funcNum] = inst;

    // ... itp.

  }

  void InstructionSet::clear()
  {
    for(auto it = commands.begin(); it != commands.end(); ++it)
    {
      delete it->second;
    }
  }




}
