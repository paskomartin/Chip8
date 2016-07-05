#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <memory>
#include <unordered_map>

namespace Chip8
{
  struct Chip8InternalData;
  struct Chip8OpcodeData;
  class Instruction;


  class InstructionSet
  {
    public:
      InstructionSet();
      ~InstructionSet();

      Instruction *GetInstruction(unsigned int key);

    private:
      void init();
      void clear();

    private:
      std::unordered_map<unsigned int, Instruction*> commands;
  //    std::unordered_map<int, Instruction2*> commands;
  };


}

#endif // INSTRUCTIONSET_H
