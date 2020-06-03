#include <fstream>
#include <unistd.h>
#include "loguru.hpp"
#include "vm.h"

VirtualMachine::VirtualMachine( uint32_t memSize, uint8_t nRegisters )
    : memSize_(memSize), nRegisters_(nRegisters), pc_(0), state_(UNSTARTED)
{
    memory_.resize(memSize_);
}

VirtualMachine::VirtualMachine( std::string stateFile, uint32_t memSize, uint8_t nRegisters )
    : VirtualMachine(memSize, nRegisters)
{
    memory_.resize(memSize_);

    std::ifstream in(stateFile);
    uint32_t index = 0;
    while (!in.eof())
    {
        in >> memory_[index++];
    }
    in.close();
}

bool VirtualMachine::load(std::vector<uint16_t> codeString)
{
    memory_ = codeString;
    return true;
}

bool VirtualMachine::run()
{
    state_ = RUNNING;

    // Code here
    while (state_ == RUNNING || state_ == PAUSED)
    {
        while (state_ == PAUSED)
        {
            usleep(500); // TODO: Use std::chrono
        }

        switch(memory_[pc_])
        {
            case HALT:
                state_ = HALTED;
                break;
            default:
                LOG_S(ERROR) << "Unknown OP: " << memory_[pc_] << "; PC = " << pc_;
                pc_++;
        };

        if (pc_ >= memSize_)
            state_ = HCF;
    }

    return true;
}

bool VirtualMachine::run(std::vector<uint16_t> codeString)
{
    load(codeString);

    return run();
}