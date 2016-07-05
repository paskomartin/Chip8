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

  Instruction *InstructionSet::GetInstruction(unsigned int key)
  {
    auto result = commands.find(key);
    if (result == commands.end())
    {
      // undefined instruction;
      return commands[0xFFFF];
    }
    return result->second;
  }

  void InstructionSet::init()
  {
    Instruction *inst = nullptr;

    inst = new CLS();
    commands[inst->key] = inst;

    inst = new RET();
    commands[inst->key] = inst;

    inst = new JP();
    commands[inst->key] = inst;

    inst = new CALL();
    commands[inst->key] = inst;

    inst = new SE();
    commands[inst->key] = inst;

    inst = new SNE();
    commands[inst->key] = inst;

    inst = new SE_REG();
    commands[inst->key] = inst;

    inst = new LD();
    commands[inst->key] = inst;

    inst = new ADD();
    commands[inst->key] = inst;

    inst = new LD_REG();
    commands[inst->key] = inst;

    inst = new OR();
    commands[inst->key] = inst;

    inst = new AND();
    commands[inst->key] = inst;

    inst = new XOR();
    commands[inst->key] = inst;

    inst = new ADC();
    commands[inst->key] = inst;

    inst = new SBC();
    commands[inst->key] = inst;

    inst = new SHR();
    commands[inst->key] = inst;

    inst = new SUBN();
    commands[inst->key] = inst;

    inst = new SHL();
    commands[inst->key] = inst;

    inst = new SNE_REG();
    commands[inst->key] = inst;

    inst = new LD_I();
    commands[inst->key] = inst;

    inst = new JP_V0();
    commands[inst->key] = inst;

    inst = new RND();
    commands[inst->key] = inst;

    inst = new DRW();
    commands[inst->key] = inst;

    inst = new SKP();
    commands[inst->key] = inst;

    inst = new SKPN();
    commands[inst->key] = inst;

    inst = new LD_VX();
    commands[inst->key] = inst;

    inst = new LD_K();
    commands[inst->key] = inst;

    inst = new LD_DT();
    commands[inst->key] = inst;

    inst = new LD_ST();
    commands[inst->key] = inst;

    inst = new ADD_I();
    commands[inst->key] = inst;

    inst = new LD_F();
    commands[inst->key] = inst;

    inst = new LD_B();
    commands[inst->key] = inst;

    inst = new LD_REG_TO_MEM();
    commands[inst->key] = inst;

    inst = new LD_MEM_TO_REG();
    commands[inst->key] = inst;

    inst = new UNDF_INSTR();
    commands[inst->key] = inst;
  }

  void InstructionSet::clear()
  {
    for(auto it = commands.begin(); it != commands.end(); ++it)
    {
      if (it->second)
      {
        delete it->second;
      }
    }
  }




}
