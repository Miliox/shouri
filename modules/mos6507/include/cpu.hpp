#pragma once

#include "regs.hpp"

#include <functional>
#include <map>

namespace mos6507
{

struct cpu_t;

using read_fn = std::function<uint8_t(uint16_t)>;
using write_fn = std::function<void(uint16_t,uint8_t)>;
using instruction_fn = std::function<uint8_t(cpu_t&)>;

struct cpu_t {
    /// Constructor
    cpu_t(read_fn read, write_fn write);

    /// Execute next instruction fetch, decode, execute and store cycle
    uint8_t cycle();

    /// Registers
    regs_t regs;

    /// Function to read from memory implementation
    const read_fn read;

    /// Function to write to memory implementation
    const write_fn write;

    /// Instruction dispatcher table
    const std::map<uint8_t, instruction_fn> dispatcher;
};

} // namespace
