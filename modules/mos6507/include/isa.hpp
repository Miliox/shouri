#pragma once
#include "regs.hpp"

namespace mos6507
{

void adc(regs_t& regs, r8_t data) noexcept;
void sbc(regs_t& regs, r8_t data) noexcept;

void land(regs_t& regs, r8_t data) noexcept;
void leor(regs_t& regs, r8_t data) noexcept;
void lora(regs_t& regs, r8_t data) noexcept;

void rol(regs_t& regs) noexcept;
void ror(regs_t& regs) noexcept;

void sec(regs_t& regs) noexcept;
void clc(regs_t& regs) noexcept;

void sed(regs_t& regs) noexcept;
void cld(regs_t& regs) noexcept;

void sei(regs_t& regs) noexcept;
void cli(regs_t& regs) noexcept;

void tax(regs_t& regs) noexcept;
void tay(regs_t& regs) noexcept;
void txa(regs_t& regs) noexcept;
void tya(regs_t& regs) noexcept;
void tsx(regs_t& regs) noexcept;
void txs(regs_t& regs) noexcept;

} // namespace