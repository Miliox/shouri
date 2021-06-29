#pragma once
#include "r8.hpp"

namespace mos6507
{
/**
 * General Purpose Flags
 */
union flags_t
{
    struct
    {
        std::uint8_t carry: 1;
        std::uint8_t zero: 1;
        std::uint8_t irq_disable: 1;
        std::uint8_t decimal: 1;
        std::uint8_t index_size: 1; // (0 - 16bit, 1 - 8bit)
        std::uint8_t mode: 1;       // (0 - 16bit, 1 - 8bit)
        std::uint8_t overflow: 1;
        std::uint8_t negative: 1;
    };
    r8_t flags;
};

/**
 * General Purpose Registers
 */
union regs_t
{
    struct
    {
        /// accumulator
        r8_t a;

        /// index-x
        r8_t x;

        /// index-y
        r8_t y;

        /// stack pointer
        r8_t sp;

        /// program counter
        r8_t pc;

        // processor status
        flags_t ps;

        /// data bank
        r8_t db; 

        /// direct page
        r8_t dp; 
    };
    std::uint64_t raw;

    consteval regs_t() { raw = 0; }
};

static_assert(sizeof(regs_t) == 8);

} // namespace