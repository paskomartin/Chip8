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
      explicit Instruction(unsigned short k) : key(k) {}
      virtual ~Instruction() {}
      virtual void execute(std::shared_ptr<Chip8InternalData>, Chip8OpcodeData& ) = 0;

      // needed for instruction set
      unsigned short key;
#if 0
      virtual std::string opcodeToString(const Chip8OpcodeData& op) = 0;
      virtual std::string opcodeToMnemonic(const Chip8InternalData& op) = 0;
#endif
  };


  // --- instructions --
  // 00E0 CLS
  class CLS : public Instruction
  {
    public:
      CLS() : Instruction(0x00E0) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData&);
  };

  // 00EE
  class RET : public Instruction
  {
    public:
      RET() : Instruction(0x00EE) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 1nnn - JP addr
  class JP : public Instruction
  {
    public:
      JP() : Instruction(0x1) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 2nnn - CALL addr
  class CALL : public Instruction
  {
    public:
      CALL() : Instruction(0x2) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  //3xkk - SE Vx, byte
  class SE : public Instruction
  {
    public:
      SE() : Instruction(0x3) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 4xkk - SNE Vx, byte
  class SNE : public Instruction
  {
    public:
      SNE() : Instruction(0x4) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 5xy0 - SE Vx, Vy
  class SE_REG : public Instruction
  {
    public:
      SE_REG() : Instruction(0x50) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  //6xkk - LD Vx, byte
  class LD : public Instruction
  {
    public:
      LD() : Instruction(0x6) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 7xkk - ADD Vx, byte
  class ADD : public Instruction
  {
    public:
      ADD() : Instruction(0x7) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy0 - LD Vx, Vy
  class LD_REG : public Instruction
  {
    public:
      LD_REG() : Instruction(0x80) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy1 - OR Vx, Vy
  class OR : public Instruction
  {
    public:
      OR() : Instruction(0x81) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy2 - AND Vx, Vy
  class AND : public Instruction
  {
    public:
      AND() : Instruction(0x82) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy3 XOR
  class XOR : public Instruction
  {
    public:
      XOR() : Instruction(0x83) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // 8xy4 - ADD with carry Vx, Vy
  class ADC : public Instruction
  {
    public:
      ADC() : Instruction(0x84) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xy5 - SUB Vx, Vy
  class SBC : public Instruction
  {
    public:
      SBC() : Instruction(0x85) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xy6 - SHR Vx {, Vy}
  class SHR : public Instruction
  {
    public:
      SHR() : Instruction(0x86) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xy7 - SUBN Vx, Vy
  class SUBN : public Instruction
  {
    public:
      SUBN() : Instruction(0x87) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 8xyE - SHL Vx {, Vy}
  class SHL : public Instruction
  {
    public:
      SHL() : Instruction(0x8E) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 9xy0 - SNE Vx, Vy
  class SNE_REG : public Instruction
  {
    public:
      SNE_REG() : Instruction(0x90) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Annn - LD I, addr
  class LD_I : public Instruction
  {
    public:
      LD_I() : Instruction(0xA) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Bnnn - JP V0, addr
  class JP_V0 : public Instruction
  {
    public:
      JP_V0() : Instruction(0xB) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  //Cxkk - RND Vx, byte
  class RND : public Instruction
  {
    public:
      RND();
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);

    private:
      std::mt19937 randGen;
  };


  // Dxyn - DRW Vx, Vy, nibble; nibble - height
  class DRW : public Instruction
  {
    public:
      DRW() : Instruction(0xD) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };


  // Ex9E - SKP Vx
  class SKP : public Instruction
  {
    public:
      SKP() : Instruction(0xE9E) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // ExA1 - SKNP Vx
  class SKPN : public Instruction
  {
    public:
      SKPN() : Instruction(0xEA1) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx07 - LD Vx, DT
  class LD_VX : public Instruction
  {
    public:
      LD_VX() : Instruction(0xF07) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx0A - LD Vx, K
  // wait for key
  class LD_K : public Instruction
  {
    public:
      LD_K() : Instruction(0xF0A) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  //Fx15 - LD DT, Vx
  // set DT, VX
  class LD_DT : public Instruction
  {
    public:
      LD_DT() : Instruction(0xF15) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx18 - LD ST, Vx
  class LD_ST : public Instruction
  {
    public:
      LD_ST() : Instruction(0xF18) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx1E - ADD I, Vx
  class ADD_I : public Instruction
  {
    public:
      ADD_I() : Instruction(0xF1E) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx29 - LD F, Vx
  // set I to location of sprite for digits.
  // digits are 4x5 so, Vx must be multiplied by 5 (row)
  // standard location of font should be started from 0x50 in memory
  class LD_F : public Instruction
  {
    public:
      LD_F() : Instruction(0xF29) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx33 - LD B, Vx
  // digit to bcd. one byte
  class LD_B : public Instruction
  {
    public:
      LD_B() : Instruction(0xF33) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx55 - LD [I], Vx
  class LD_REG_TO_MEM : public Instruction
  {
    public:
      LD_REG_TO_MEM() : Instruction(0xF55) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // Fx65 - LD Vx, [I]
  class LD_MEM_TO_REG : public Instruction
  {
    public:
      LD_MEM_TO_REG() : Instruction(0xF65) {}
      void execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op);
  };

  // 0xFFFF
  // Undefined instruction
  class UNDF_INSTR : public Instruction
  {
    public:
      UNDF_INSTR() : Instruction(0xFFFF) {}
      void execute(std::shared_ptr<Chip8InternalData>, Chip8OpcodeData &op);
  };



}
#endif // INSTRUCTION_H
