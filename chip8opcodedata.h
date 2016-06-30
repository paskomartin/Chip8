#ifndef CHIP8OPCODEDATA_H
#define CHIP8OPCODEDATA_H

namespace Chip8
{

  // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
  struct Chip8OpcodeData
  {
      unsigned short opcode;
      unsigned char funcNum;
      unsigned int nnn;         // address for some instruction
      unsigned short kk;        // lowesst 8 bit of the instr
      unsigned char subFuncNum; // lowest nibble  of opcode
      unsigned char x;
      unsigned char y;
      //unsigned char *Vx;        // pointers to proper registers
      //unsigned char *Vy;        //
  };


}

#endif // CHIP8OPCODEDATA_H
