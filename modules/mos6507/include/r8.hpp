#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace mos6507
{
union r8_t
{
    std::uint8_t raw;
    struct bytes_t
    {
        std::uint8_t byte0: 8;
    } bytes;
    struct nibbles_t
    {
        std::uint8_t nibble0: 4;
        std::uint8_t nibble1: 4;
    } nibbles;
    struct bits_t
    {
        std::uint8_t bit0: 1;
        std::uint8_t bit1: 1;
        std::uint8_t bit2: 1;
        std::uint8_t bit3: 1;
        std::uint8_t bit4: 1;
        std::uint8_t bit5: 1;
        std::uint8_t bit6: 1;
        std::uint8_t bit7: 1;

        constexpr __attribute__((always_inline)) std::uint8_t msb() const { return bit7; }
        constexpr __attribute__((always_inline)) std::uint8_t lsb() const { return bit0; }

        constexpr __attribute__((always_inline)) std::uint8_t operator[](std::size_t bit)
        {
            switch (bit)
            {
            case 0: return bit0;
            case 1: return bit1;
            case 2: return bit2;
            case 3: return bit3;
            case 4: return bit4;
            case 5: return bit5;
            case 6: return bit6;
            case 7: return bit7;
            default: return 0;
            }
        }

        constexpr __attribute__((always_inline)) std::uint8_t operator[](std::size_t bit) const
        {
            switch (bit)
            {
            case 0: return bit0;
            case 1: return bit1;
            case 2: return bit2;
            case 3: return bit3;
            case 4: return bit4;
            case 5: return bit5;
            case 6: return bit6;
            case 7: return bit7;
            default: return 0;
            }
        }
    } bits;

    consteval r8_t() : raw(0) { }
    constexpr __attribute__((always_inline)) r8_t(std::uint8_t b) : raw(b) { }
    constexpr __attribute__((always_inline)) r8_t(const r8_t &rhs) { this->raw = rhs.raw ; }

    static consteval r8_t min() { return r8_t(0x00); }
    static consteval r8_t zero() { return r8_t(0x00); }
    static consteval r8_t max() { return r8_t(0xFF); }

    constexpr __attribute__((always_inline)) r8_t& operator=(r8_t rhs)
    {
        this->raw = rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator=(std::uint8_t rhs)
    {
        this->raw = rhs;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator+=(const r8_t& rhs)
    {
        this->raw += rhs.raw;
        return *this;
    }

    // prefix
    constexpr __attribute__((always_inline)) r8_t& operator++()
    {
        this->raw += 1;
        return *this;
    }

    // postfix
    constexpr __attribute__((always_inline)) r8_t operator++(int)
    {
        r8_t prev = *this;
        operator++();
        return prev;
    }

    constexpr __attribute__((always_inline)) r8_t& operator-=(const r8_t& rhs)
    {
        this->raw -= rhs.raw;
        return *this;
    }

    // prefix
    constexpr __attribute__((always_inline)) r8_t& operator--()
    {
        this->raw -= 1;
        return *this;
    }

    // postfix
    constexpr __attribute__((always_inline)) r8_t operator--(int)
    {
        r8_t
     prev = *this;
        operator--();
        return prev;
    }

    constexpr __attribute__((always_inline)) r8_t& operator*=(const r8_t& rhs)
    {
        this->raw *= rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator/=(const r8_t& rhs)
    {
        this->raw /= rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator%=(const r8_t& rhs)
    {
        this->raw %= rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator^=(const r8_t& rhs)
    {
        this->raw ^= rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator&=(const r8_t& rhs)
    {
        this->raw &= rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator|=(const r8_t& rhs)
    {
        this->raw |= rhs.raw;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator>>=(int shift)
    {
        this->raw >>= shift;
        return *this;
    }

    constexpr __attribute__((always_inline)) r8_t& operator<<=(int shift)
    {
        this->raw <<= shift;
        return *this;
    }

    friend constexpr __attribute__((always_inline)) r8_t operator+(r8_t lhs) { return r8_t(+lhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator-(r8_t lhs) { return r8_t(-lhs.raw); }

    friend constexpr __attribute__((always_inline)) r8_t operator+(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw + rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator-(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw - rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator*(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw * rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator/(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw / rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator%(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw % rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator&(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw & rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator|(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw | rhs.raw); }
    friend constexpr __attribute__((always_inline)) r8_t operator^(r8_t lhs, r8_t rhs) { return r8_t(lhs.raw ^ rhs.raw); }

    friend constexpr __attribute__((always_inline)) r8_t operator+(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw + rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator-(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw - rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator*(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw * rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator/(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw / rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator%(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw % rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator&(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw & rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator|(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw | rhs); }
    friend constexpr __attribute__((always_inline)) r8_t operator^(r8_t lhs, std::uint8_t rhs) { return r8_t(lhs.raw ^ rhs); }

    friend constexpr __attribute__((always_inline)) r8_t operator~(r8_t lhs) { return r8_t(~lhs.raw); }

    friend constexpr __attribute__((always_inline)) bool operator< (r8_t lhs, r8_t rhs){ return lhs.raw <  rhs.raw; }
    friend constexpr __attribute__((always_inline)) bool operator> (r8_t lhs, r8_t rhs){ return lhs.raw >  rhs.raw; }
    friend constexpr __attribute__((always_inline)) bool operator<=(r8_t lhs, r8_t rhs){ return lhs.raw <= rhs.raw; }
    friend constexpr __attribute__((always_inline)) bool operator>=(r8_t lhs, r8_t rhs){ return lhs.raw >= rhs.raw; }
    friend constexpr __attribute__((always_inline)) bool operator==(r8_t lhs, r8_t rhs){ return lhs.raw == rhs.raw; }
    friend constexpr __attribute__((always_inline)) bool operator!=(r8_t lhs, r8_t rhs){ return lhs.raw != rhs.raw; }

    friend constexpr __attribute__((always_inline)) r8_t operator>>(r8_t lhs, int shift){ return r8_t(lhs.raw >> shift); }
    friend constexpr __attribute__((always_inline)) r8_t operator<<(r8_t lhs, int shift){ return r8_t(lhs.raw << shift); }

    constexpr bool __attribute__((always_inline)) will_add_overflow(r8_t rhs) const
    {
        r8_t max(r8_t::max());
        return (this->raw) > (max.raw - rhs.raw);
    }

    constexpr __attribute__((always_inline)) bool will_sub_overflow(r8_t rhs) const
    {
        return this->raw < rhs.raw;
    }
};

static_assert(sizeof(r8_t) == 1);
static_assert(r8_t::zero() == 0);
static_assert(r8_t::min() == 0);
static_assert(r8_t::max() == 255);
static_assert(r8_t()++ == 0);
static_assert(++r8_t() == 1);
static_assert(r8_t()-- == 0);
static_assert(--r8_t() == 255);
static_assert(~r8_t() == 255);
static_assert(+r8_t(1) == 1);
static_assert(-r8_t(1) == 255);
static_assert((r8_t(1) << 7) == 128);
static_assert((r8_t(1) >> 1) == 0);
static_assert((r8_t(1) + r8_t(2)) == 3);
static_assert((r8_t(1) - r8_t(2)) == 255);
static_assert((r8_t(1) * r8_t(2)) == 2);
static_assert((r8_t(1) / r8_t(2)) == 0);
static_assert((r8_t(1) % r8_t(2)) == 1);
static_assert((r8_t(1) & r8_t(2)) == 0);
static_assert((r8_t(1) | r8_t(2)) == 3);
static_assert((r8_t(1) ^ r8_t(2)) == 3);
static_assert((r8_t(1) < r8_t(2)) == true);
static_assert((r8_t(1) > r8_t(2)) == false);
static_assert((r8_t(1) == r8_t(2)) == false);
static_assert((r8_t(1) != r8_t(2)) == true);
static_assert((r8_t(254).will_add_overflow(r8_t(1))) == false);
static_assert((r8_t(255).will_add_overflow(r8_t(1))) == true);
static_assert((r8_t(1).will_sub_overflow(r8_t(1))) == false);
static_assert((r8_t(1).will_sub_overflow(r8_t(2))) == true);
} // namespace