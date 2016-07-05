#ifndef CHIP8INTERNALDATA_H
#define CHIP8INTERNALDATA_H

#include <array>

namespace Chip8
{

  struct Chip8InternalData
  {
      static const unsigned int MAX_REGISTERS = 16;
      static const unsigned int CARRY = MAX_REGISTERS - 1;
      static const unsigned int MAX_KEYS = 16;
      static const unsigned int MAX_STACK = 16;
      static const unsigned int SCREEN_W = 64;
      static const unsigned int SCREEN_H = 32;

      static const unsigned int fontBIOSPosition = 0x50;

      std::array<unsigned char, 0x1000> memory; // 4kb memory
      std::array<unsigned short, MAX_STACK> stack;
      unsigned short SP = 0;              // stack pointer
      unsigned short I = 0;               // index register
      unsigned short PC = 0x200;          // program counter
      std::array<unsigned char, MAX_REGISTERS> V;
      std::array<unsigned char, SCREEN_W * SCREEN_H> screen;
      std::array<unsigned char, MAX_KEYS> keys;// { 0 };
      unsigned char delayTimer = 0;
      unsigned char soundTimer = 0;
      unsigned char * const carryReg = &V[MAX_REGISTERS - 1];

      // TODO: Halt flag when is error!
      //bool haltFlag = false;


      //enum { MAX_REGISTER = 16, MAX_KEYS = 16, SCREEN_W = 64, SCREEN_H = 32 } ;
      //unsigned char memory[0x1000] {0};   // 4k memory
      //unsigned short stack[16] {0};       //
      //unsigned char V[MAX_REGISTERS ] {0}; // 16 general registers. V[15] carry flag
      //unsigned char screen[SCREEN_W * SCREEN_H] { 0 } ;


      inline void AdvancePC(unsigned int step = 2)
      {
        PC = (PC + step) & 0xFFF;
      }

      inline unsigned char GetCarry() const
      {
        return *carryReg;
      }

      inline void SetCarry(const unsigned char val)
      {
        *carryReg = val;
      }

      inline bool IsKeyPressed(unsigned char key)
      {
        return keys[key]; // & 0xf];
      }

  };

}

#endif // CHIP8INTERNALDATA_H
