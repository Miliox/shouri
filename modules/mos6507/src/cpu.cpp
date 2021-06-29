#include "cpu.hpp"

uint8_t nop(mos6507::cpu_t&)
{
    return 2;
}

mos6507::cpu_t::cpu_t(read_fn read, write_fn write) : regs(), read(std::move(read)), write(std::move(write))
    , dispatcher({
        {0xEA, nop},
    })
{

}

uint8_t mos6507::cpu_t::cycle()
{
    // Fetch
    uint8_t code = read(regs.pc++);

    // Decode
    auto& op = dispatcher.at(code);

    // Execute & Store
    return op(*this);
}