#include "isa.hpp"

void mos6507::adc(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    data += regs.r.ps.flags.carry;
    auto acc = regs.r.a + data;

    regs.r.ps.flags.negative = acc.bits.msb();
    regs.r.ps.flags.zero     = acc == 0;
    regs.r.ps.flags.overflow = regs.r.a.bits.msb() == data.bits.msb() &&
                               regs.r.a.bits.msb() != acc.bits.msb();
    regs.r.ps.flags.carry    = regs.r.a.will_add_overflow(data);

    regs.r.a = acc;
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
    regs.r.a &= data;

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::leor(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    regs.r.a ^= data;

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::lora(mos6507::regs_t& regs, mos6507::r8_t data) noexcept
{
    regs.r.a |= data;

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::rol(mos6507::regs_t& regs) noexcept
{
    regs.r.a = (regs.r.a << 1) | (regs.r.a.bits.bit7);

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::ror(mos6507::regs_t& regs) noexcept
{
    regs.r.a = (regs.r.a >> 1) | (regs.r.a.bits.bit0 << 7);

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::sec(mos6507::regs_t& regs) noexcept
{
    regs.r.ps.flags.carry = 1;
}

void mos6507::clc(mos6507::regs_t& regs) noexcept
{
    regs.r.ps.flags.carry = 0;
}

void mos6507::sed(mos6507::regs_t& regs) noexcept
{
    regs.r.ps.flags.decimal = 1;
}

void mos6507::cld(mos6507::regs_t& regs) noexcept
{
    regs.r.ps.flags.decimal = 0;
}

void mos6507::sei(mos6507::regs_t& regs) noexcept
{
    regs.r.ps.flags.irq_disable = 1;
}

void mos6507::cli(mos6507::regs_t& regs) noexcept
{
    regs.r.ps.flags.irq_disable = 0;
}

void mos6507::tax(mos6507::regs_t& regs) noexcept
{
    regs.r.x = regs.r.a;

    regs.r.ps.flags.negative = regs.r.x.bits.msb();
    regs.r.ps.flags.zero     = regs.r.x == 0;
}

void mos6507::tay(mos6507::regs_t& regs) noexcept
{
    regs.r.y = regs.r.a;

    regs.r.ps.flags.negative = regs.r.y.bits.msb();
    regs.r.ps.flags.zero     = regs.r.y == 0;
}

void mos6507::txa(mos6507::regs_t& regs) noexcept
{
    regs.r.a = regs.r.x;

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::tya(mos6507::regs_t& regs) noexcept
{
    regs.r.a = regs.r.y;

    regs.r.ps.flags.negative = regs.r.a.bits.msb();
    regs.r.ps.flags.zero     = regs.r.a == 0;
}

void mos6507::tsx(mos6507::regs_t& regs) noexcept
{
    regs.r.x = regs.r.sp;

    regs.r.ps.flags.negative = regs.r.x.bits.msb();
    regs.r.ps.flags.zero     = regs.r.x == 0;
}

void mos6507::txs(mos6507::regs_t& regs) noexcept
{
    regs.r.sp = regs.r.x;
}
