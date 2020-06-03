#pragma once

#include <string>
#include <vector>

class VirtualMachine
{
    public:

        enum State { UNSTARTED, RUNNING, PAUSED, HALTED, HCF };
        enum Operations {
            HALT = 0
        };

        VirtualMachine(
            uint32_t memSize=1024,
            uint8_t  nRegisters=8
        );

        VirtualMachine(
            std::string stateFile,
            uint32_t    memSize=1024,
            uint8_t     nRegisters=8
        );

        bool load(std::vector<uint16_t> codeString);

        bool run();
        bool run(std::vector<uint16_t> codeString);

        State getState() { return state_; }

    private:
        uint32_t memSize_;
        uint8_t  nRegisters_;

        uint32_t pc_;

        State state_;

        std::vector<uint16_t> memory_;
};