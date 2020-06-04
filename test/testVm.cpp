#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"
#include <gtest/gtest.h>
#include <vector>
#include "vm.h"

class VmUnitTests : public ::testing::Test 
{

protected:
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

TEST_F(VmUnitTests, testVm_createBasic)
{
    VirtualMachine vm;
}

TEST_F(VmUnitTests, testVm_createBasicAndLoad)
{
    std::vector<uint16_t> program = {0};

    VirtualMachine vm;
    ASSERT_TRUE(vm.load(program));
}

TEST_F(VmUnitTests, testVm_createBasicAndRun)
{
    std::vector<uint16_t> program = {0};
    
    VirtualMachine vm;
    ASSERT_TRUE(vm.run(program));
}

TEST_F(VmUnitTests, testVm_createBasic_loadAndRun)
{
    std::vector<uint16_t> program = {0};
    
    VirtualMachine vm;
    ASSERT_TRUE(vm.load(program));
    ASSERT_TRUE(vm.run());
}

TEST_F(VmUnitTests, testVm_isHalted)
{
    std::vector<uint16_t> program = {0};
    
    VirtualMachine vm;
    vm.load(program);
    vm.run();

    ASSERT_EQ(vm.getState(), VirtualMachine::HALTED);
}

TEST_F(VmUnitTests, testVm_parseHalted)
{
    std::vector<uint16_t> program = {0, 133, 22342, 314, 4123, 4029};
    
    VirtualMachine vm;
    vm.load(program);
    vm.run();

    ASSERT_EQ(vm.getState(), VirtualMachine::HALTED);
}

TEST_F(VmUnitTests, testVm_parseGarblyGook)
{
    std::vector<uint16_t> program = {133, 22342, 314, 4123, 4029, 0};
    
    VirtualMachine vm;
    vm.load(program);
    vm.run();

    ASSERT_EQ(vm.getState(), VirtualMachine::HALTED);
}

TEST_F(VmUnitTests, testVm_haltAndCatchFire)
{
    std::vector<uint16_t> program = {133, 22342, 314, 4123, 4029};
    
    VirtualMachine vm(5);   // Set memsize to 5
    vm.load(program);
    vm.run();

    ASSERT_EQ(vm.getState(), VirtualMachine::HCF);
}

TEST_F(VmUnitTests, testVm_parseOut)
{
    std::vector<uint16_t> program = {19, 65, 0};
    
    VirtualMachine vm;
    std::queue<uint16_t> outputQueue;
    vm.connectOutput(&outputQueue);
    vm.load(program);
    vm.run();

    ASSERT_EQ(vm.getState(), VirtualMachine::HALTED);
    ASSERT_EQ(outputQueue.size(), 1);
    ASSERT_EQ(outputQueue.front(), 65);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    loguru::init(argc, argv);
    loguru::g_stderr_verbosity = loguru::Verbosity_MAX;

    LOG_S(INFO) << "Testing basic build.";

    return RUN_ALL_TESTS();
}
