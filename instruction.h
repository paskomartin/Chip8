#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <memory>



namespace Chip8
{

  struct Chip8InternalData;
  struct Chip8OpcodeData;


  class Instruction
  {
    public:
      virtual ~Instruction() {}
      virtual void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData& op) = 0;
#if 0
      virtual std::string opcodeToString(const Chip8OpcodeData& op) = 0;
      virtual std::string opcodeToMnemonic(const Chip8InternalData& op) = 0;
#endif
  };

  class XorInstruction : public Instruction
  {
      // Instruction interface
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


}

#endif // INSTRUCTION_H
