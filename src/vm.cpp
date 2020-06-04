#include <fstream>
#include <iostream>
#include <unistd.h>
#include "loguru.hpp"
#include "vm.h"

VirtualMachine::VirtualMachine( uint32_t memSize, uint8_t nRegisters )
    : memSize_(memSize), nRegisters_(nRegisters), pc_(0), state_(UNSTARTED)
{
    memory_.resize(memSize_);
    outputQueue_ = nullptr;
    inputQueue_ = nullptr;
    outputStream_ = nullptr;
    inputStream_ = nullptr;
}

VirtualMachine::VirtualMachine( std::string stateFile, uint32_t memSize, uint8_t nRegisters )
    : VirtualMachine(memSize, nRegisters)
{
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
            case OUT:
                opOut(memory_[++pc_]);
                pc_++;
                break;
            default:
                LOG_S(ERROR) << "Unknown OP: " << memory_[pc_] << "; PC = " << pc_;
                pc_++;
        };

        if (pc_ >= memSize_)
        {
            state_ = HCF;
            LOG_S(ERROR) << "Ran into HCF condition.  End of memory.";
        }
    }

    return true;
}

bool VirtualMachine::run(std::vector<uint16_t> codeString)
{
    load(codeString);

    return run();
}

void VirtualMachine::connectOutput(std::queue<uint16_t>* outputQueue)
{
    outputQueue_ = outputQueue;
}

void VirtualMachine::connectInput(std::queue<uint16_t>* inputQueue)
{
    inputQueue_ = inputQueue;
}

void VirtualMachine::connectOutput(std::ostream* outputStream)
{
    outputStream_ = outputStream;
}

void VirtualMachine::connectInput(std::istream* inputStream)
{
    inputStream_ = inputStream;
}


void VirtualMachine::opOut(uint16_t i)
{
    if (outputQueue_)
        outputQueue_->push(i);
    if (outputStream_)
        (*outputStream_) << (char)i;
    std::cout << (char)i;
}
