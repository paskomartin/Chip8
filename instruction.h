#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <memory>
#include <random>
#include <chrono>

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


  // --- instructions --
  // 00E0 CLS
  class Cls : public Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData&);
  };


  class Ret : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 1nnn - JP addr
  class JP : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 2nnn - CALL addr
  class Call : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  //3xkk - SE Vx, byte
  class SE : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 4xkk - SNE Vx, byte
  class SNE : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 5xy0 - SE Vx, Vy
  class SE_REG : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  //6xkk - LD Vx, byte
  class LD : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 7xkk - ADD Vx, byte
  class ADD : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy0 - LD Vx, Vy
  class LD_REG : Instruction
  {
    public:
       void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy1 - OR Vx, Vy
  class OR : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy2 - AND Vx, Vy
  class AND : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy3 XOR
  class XOR : public Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy4 - ADD with carry Vx, Vy
  class ADC : public Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xy5 - SUB Vx, Vy
  class SBC : public Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xy6 - SHR Vx {, Vy}
  class SHR : public Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  class SUBN : public Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xyE - SHL Vx {, Vy}
  class SHL : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 9xy0 - SNE Vx, Vy
  class SNE_REG : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Annn - LD I, addr
  class LD_I : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Bnnn - JP V0, addr
  class JP_V0 : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  //Cxkk - RND Vx, byte
  class RND : Instruction
  {
    public:
      RND();
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);

    private:
      std::mt19937 randGen;
  };


  // TODO: LATER
  class DRW : Instruction
  {
    public:
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };
}
#endif // INSTRUCTION_H
