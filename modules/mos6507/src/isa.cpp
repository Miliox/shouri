#include "isa.hpp"

void mos6507::adc(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    data += regs.ps.carry;
    auto acc = regs.a + data;

    regs.ps.negative = acc.bits.msb();
    regs.ps.zero     = acc == 0;
    regs.ps.overflow = regs.a.bits.msb() == data.bits.msb() &&
                             regs.a.bits.msb() != acc.bits.msb();
    regs.ps.carry    = regs.a.will_add_overflow(data);

    regs.a = acc;
}

void mos6507::sbc(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    // complement of 2
    data = r8_t::max() - data;
    data += 1;

    mos6507::adc(regs, data);
}

void mos6507::land(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    regs.a &= data;

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::leor(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    regs.a ^= data;

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::lora(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    regs.a |= data;

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::rol(mos6507::regs_t& regs) noexcept
{
    regs.a = (regs.a << 1) | (regs.a.bits.bit7);

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::ror(mos6507::regs_t& regs) noexcept
{
    regs.a = (regs.a >> 1) | (regs.a.bits.bit0 << 7);

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::sec(mos6507::regs_t& regs) noexcept
{
    regs.ps.carry = 1;
}

void mos6507::clc(mos6507::regs_t& regs) noexcept
{
    regs.ps.carry = 0;
}

void mos6507::sed(mos6507::regs_t& regs) noexcept
{
    regs.ps.decimal = 1;
}

void mos6507::cld(mos6507::regs_t& regs) noexcept
{
    regs.ps.decimal = 0;
}

void mos6507::sei(mos6507::regs_t& regs) noexcept
{
    regs.ps.irq_disable = 1;
}

void mos6507::cli(mos6507::regs_t& regs) noexcept
{
    regs.ps.irq_disable = 0;
}

void mos6507::tax(mos6507::regs_t& regs) noexcept
{
    regs.x = regs.a;

    regs.ps.negative = regs.x.bits.msb();
    regs.ps.zero     = regs.x == 0;
}

void mos6507::tay(mos6507::regs_t& regs) noexcept
{
    regs.y = regs.a;

    regs.ps.negative = regs.y.bits.msb();
    regs.ps.zero     = regs.y == 0;
}

void mos6507::txa(mos6507::regs_t& regs) noexcept
{
    regs.a = regs.x;

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::tya(mos6507::regs_t& regs) noexcept
{
    regs.a = regs.y;

    regs.ps.negative = regs.a.bits.msb();
    regs.ps.zero     = regs.a == 0;
}

void mos6507::tsx(mos6507::regs_t& regs) noexcept
{
    regs.x = regs.sp;

    regs.ps.negative = regs.x.bits.msb();
    regs.ps.zero     = regs.x == 0;
}

void mos6507::txs(mos6507::regs_t& regs) noexcept
{
    regs.sp = regs.x;
}
