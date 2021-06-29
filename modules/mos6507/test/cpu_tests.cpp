#include <gtest/gtest.h>
#include "cpu.hpp"

using namespace mos6507;

TEST (CPU_INSTR, NOP_IncrementPcByOne_ExpectPcIsOne)
{
  cpu_t cpu([](uint16_t) -> uint8_t { return 0xEA; }, [](uint16_t,uint8_t){});
  EXPECT_EQ(0, cpu.regs.pc);
  EXPECT_EQ(2, cpu.cycle());
  EXPECT_EQ(1, cpu.regs.pc);
  EXPECT_EQ(0, cpu.regs.ps.flags);
}
