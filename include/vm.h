#pragma once

#include <string>
#include <vector>
#include <queue>

class VirtualMachine
{
    public:

        enum State { UNSTARTED, RUNNING, PAUSED, HALTED, HCF };
        enum Operations {
            HALT = 0,
            SET = 1,
            PUSH = 2,
            POP = 3,
            EQ = 4,
            GT = 5,
            JMP = 6,
            JT = 7,
            JF = 8,
            ADD = 9,
            MULT = 10,
            MOD = 11,
            AND = 12,
            OR = 13,
            NOT = 14,
            RMEM = 15,
            WMEM = 16,
            CALL = 17,
            RET = 18,
            OUT = 19,
            IN = 20,
            NOOP = 21
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

        void connectOutput(std::queue<uint16_t>* outputQueue);
        void connectInput(std::queue<uint16_t>* inputQueue);

        void connectOutput(std::ostream* outputQueue);
        void connectInput(std::istream* inputQueue);

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

        std::queue<uint16_t>* outputQueue_;
        std::queue<uint16_t>* inputQueue_;

        std::ostream* outputStream_;
        std::istream* inputStream_;

        void opOut(uint16_t i);
};