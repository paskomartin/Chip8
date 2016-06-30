#include "instruction.h"
#include "chip8internaldata.h"
#include "chip8opcodedata.h"

namespace Chip8
{


void XorInstruction::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
{
  //std::shared_ptr<Chip8::Chip8InternalData> ptr;
  //auto ptr = std::make_shared<Chip8InternalData>(chip);
  chip->V[op.x] ^=  chip->V[op.y];
  //*(op.Vx) ^= *(op.Vy);
}



}
