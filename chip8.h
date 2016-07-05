#ifndef CHIP8_H
#define CHIP8_H

#include <string>
#include <memory>

namespace Chip8
{

struct Chip8InternalData;
struct Chip8OpcodeData;
class InstructionSet;

class Chip8
{
  public:
    Chip8();

    bool load(const std::string& filename, unsigned int pos = 0x200);
    void execute();

  private:
    void init();

    unsigned short fetchOpcode();
    void decodeOpcode(Chip8OpcodeData &op);
    void executeOpcode(Chip8OpcodeData &op);

    void increasePC(unsigned int counter = 2);
    void setCarryFlag();
    void unsetCarryFlag();

  private:
    std::shared_ptr<Chip8InternalData> data;
    std::shared_ptr<InstructionSet> instructions;
};


}

#endif // CHIP8_H
