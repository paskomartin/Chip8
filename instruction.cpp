#include <stdexcept>
#include <iostream>
#include "instruction.h"
#include "chip8internaldata.h"
#include "chip8opcodedata.h"

namespace Chip8
{
  void CLS::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData & /*op*/)
  {
    chip->screen.fill(0);
    //chip->PC = (chip->PC + 2) & 0xFFF;
    chip->AdvancePC();
  }

  void RET::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData & /*op*/)
  {
    chip->PC = chip->stack[chip->SP];
    --chip->SP;
    // TODO: CHECK STACK POINTER?
  }


  void JP::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->PC = op.nnn;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void CALL::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    /* TODO: Maybe this isn't a good choice. It will be better to increase
     * stack pointer, check if is equal MAX_STACK and after throw ERROR
     */
    //chip->SP = (chip->SP + 1) & chip->MAX_STACK;

    ++chip->SP;
    if (chip->SP >= chip->MAX_STACK)
      throw std::out_of_range("Stack is out of bound.");

    chip->stack[chip->SP] = chip->PC;
    chip->PC = op.nnn;
  }


  void SE::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if ( chip->V[op.x] == op.kk )
    {
      chip->AdvancePC();
      //chip->PC = (chip->PC + 2) & 0xFFF;
    }
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void SNE::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if (chip->V[op.x] != op.kk)
    {
      chip->AdvancePC();
      //chip->PC = (chip->PC + 2) & 0xFFF;
    }
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void SE_REG::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if (chip->V[op.x] == chip->V[op.y])
    {
      chip->AdvancePC();
      //chip->PC = (chip->PC + 2) & 0xFFF;
    }
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void LD::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] = op.kk;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void ADD::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] += op.kk;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void LD_REG::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] = chip->V[op.y];
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void OR::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] |= chip->V[op.y];
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void AND::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] &= chip->V[op.y];
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void XOR::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] ^=  chip->V[op.y];
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void ADC::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    unsigned short result = chip->V[op.x] + chip->V[op.y];
    *chip->carryReg = (result >> 8); // set or unset carry
    // set result
    chip->V[op.x] = result & 0xFF;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void SBC::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if(chip->V[op.x] > chip->V[op.y])
    {
      //chip->V[ chip->MAX_REGISTERS - 1] = 0;
      chip->SetCarry(0);
    }
    else
    {
      chip->SetCarry(1);
      //chip->V[ chip->MAX_REGISTERS - 1] = 1;
    }
    chip->V[op.x] -= chip->V[op.y];
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void SHR::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[ chip->MAX_REGISTERS - 1] = chip->V[op.x] & 0x1;
    chip->V[op.x] >>= 1;

    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }

  void SUBN::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if ( chip->V[op.y] > chip->V[op.x] )
    {
      chip->SetCarry(1);
      //*chip->carryReg = 1;
      //chip->V[ chip->CARRY ] = 1;
    }
    else
    {
      chip->SetCarry(0);
      //*chip->carryReg = 0;
      //chip->V[ chip->CARRY ] = 0;
    }

    chip->V[op.x] = chip->V[op.y] - chip->V[op.x];

    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }

  void SHL::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    //chip->V[ chip->CARRY ] = ( chip->V[op.x] >> 7);
    *chip->carryReg = ( chip->V[op.x] >> 7);
    chip->V[ op.x ] <<= 1;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }


  void SNE_REG::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if (chip->V[op.x] != chip->V[op.y])
    {
      chip->AdvancePC();
       //chip->PC = (chip->PC + 2) & 0xFFF;
    }
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }

  void LD_I::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->I = op.nnn;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }

  void JP_V0::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->PC = op.nnn + chip->V[0];
  }

  RND::RND() : Instruction(0xC)
  {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    randGen.seed(seed);
  }

  void RND::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    int rnd = (randGen() & 0xFF) & op.kk;
    chip->V[op.x] = rnd;
    chip->AdvancePC();
    //chip->PC = (chip->PC + 2) & 0xFFF;
  }

  void DRW::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    unsigned short spriteByte = 0;

    //chip->V[ chip->CARRY ] = 0
    // reset carry
    //*chip->carryReg = 0;
    chip->SetCarry(0);

    // sprite row
    for (int row = 0; row < op.n; ++row)
    {
      // get next sprite byte
      spriteByte = chip->memory[ chip->I + row ];

      // there are 8 pixels in each byte
      // starts from 7 bit.
      for (int col = 0; col < 8; ++col)
      {
        //
        if ( (spriteByte & (0x80 >> col ) ) != 0 )
        {
          // check if is setted pixel on the screen
          /* loc = x + y * width:
           *
           * x = sprite.x + screen.x
           * y = sprite.y + screen.y
           * width = screen.height
           *
           */
          int loc = ( op.x + col ) + ( (row + op.y) * chip->SCREEN_W);

          if(chip->screen[loc] == 1)
          {
            chip->SetCarry(1);
            //*chip->carryReg = 1;
          }

          chip->screen[loc] ^= 1;
        }
      }
    }
    chip->AdvancePC();
    //chip->PC += (chip->PC + 2) & 0xFFF;
  }


  void SKP::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if (chip->IsKeyPressed( op.x ) )
    {
      chip->AdvancePC();
    }
    chip->AdvancePC();
  }


  void SKPN::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    if ( !chip->IsKeyPressed( op.x ))
    {
      chip->AdvancePC();
    }
    chip->AdvancePC();
  }


  void LD_VX::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->V[op.x] = chip->delayTimer;
    chip->AdvancePC();
  }


  void LD_K::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    for(unsigned char key = 0; key < chip->keys.size(); ++key)
    {
      // if key is pressed, set the key number to the Vx
      // and set PC += 2
      if (chip->keys[key] != 0)
      {
        chip->V[ op.x ] = key;
        chip->AdvancePC();
        return;
      }
      // otherwise do LD_K in another cpu cycle
    }
  }


  void LD_DT::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->delayTimer = chip->V[ op.x ];
    chip->AdvancePC();
  }


  void LD_ST::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->soundTimer = chip->V[ op.x ];
    chip->AdvancePC();
  }


  void ADD_I::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    chip->I = chip->V[ op.x ];
    chip->AdvancePC();
  }

  void LD_F::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    // Each letter is 4 width and 5 height, so it needs to multiply by 5
    // (because is an offset where each letter starts)
    // eg. x = 6, so programmer want to display number 6 on screen
    // I must be setted like this: 0x50 + letter_number * height_of_letter
    chip->I = chip->fontBIOSPosition + (chip->V[op.x] * 5);
    chip->AdvancePC();
  }


  void LD_B::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    unsigned char val = chip->V[op.x];
    // hundreds
    chip->memory[ chip->I ] = ( val / 100 ) % 10;
    chip->memory[ chip->I + 1 ] = ( val / 10 ) % 10;
    chip->memory[ chip->I + 2 ] = val % 10;

    chip->AdvancePC();
  }


  void LD_REG_TO_MEM::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    for (unsigned char i = 0; i <= op.x; ++i)
    {
      chip->memory[ chip->I & 0xFFF ] = chip->V[i];
      ++chip->I;
    }
    chip->AdvancePC();
  }

  void LD_MEM_TO_REG::execute(std::shared_ptr<Chip8InternalData> chip, Chip8OpcodeData &op)
  {
    for (unsigned int i = 0; i <= op.x; ++i)
    {
      chip->V[i] = chip->memory[ chip->I & 0xFFF ];
      ++chip->I;
    }
    chip->AdvancePC();
  }

  void UNDF_INSTR::execute(std::shared_ptr<Chip8InternalData> /*chip*/, Chip8OpcodeData &op)
  {
    std::cerr << "Undefined opcode: " << op.opcode << "\n";
    // TODO: Warning message
  }


}



