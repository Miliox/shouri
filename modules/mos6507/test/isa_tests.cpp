#include <gtest/gtest.h>
#include "isa.hpp"

TEST (Mos6507_ISA, ADC_AddZeroAccWithOneAndWithCarry_EqualsTwo)
{
  mos6507::regs_t regs;
  regs.ps.carry = 1;

  EXPECT_EQ(0, regs.a);

  mos6507::adc(regs, 1);

  EXPECT_EQ(2, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}


TEST (Mos6507_ISA, ADC_AddZeroAccWithOneWithoutCarry_EqualsOne)
{
  mos6507::regs_t regs;
  regs.ps.carry = 0;

  EXPECT_EQ(0, regs.a);

  mos6507::adc(regs, 1);

  EXPECT_EQ(1, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_SubtractOneWithOneWithoutCarry_EqualsZero) {
  mos6507::regs_t regs;
  regs.a = 1;
  regs.ps.carry = 0;

  mos6507::sbc(regs, 1);

  EXPECT_EQ(0, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}


TEST (Mos6507_ISA, SBC_SubtractOneWithOneWithCarry_EqualsOne)
{
  mos6507::regs_t regs;
  regs.a = 1;
  regs.ps.carry = 1;

  mos6507::sbc(regs, 1);

  EXPECT_EQ(1, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

/*
 ADC Overflow Logic
 source: http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
|--------------|--------------|---------------------------------------------|
| Input        | Output       | Example                                     |
|--------------|--------------|---------------------------------------------|
| M7 | N7 | C6 | C7 | S7 | V  | Hex             | Unsigned    | Signed      |
|----|----|----|----|----|----|-----------------|-------------|-------------|
| 0  | 0  | 0  | 0  | 0  | 0  | 0x50+0x10=0x60  | 80+16=96    | 80+16=96    |
| 0  | 0  | 1  | 0  | 1  | 1  | 0x50+0x50=0xa0  | 80+80=160   | 80+80=-96   |
| 0  | 1  | 0  | 0  | 1  | 0  | 0x50+0x90=0xe0  | 80+144=224  | 80+-112=-32 |
| 0  | 1  | 1  | 1  | 0  | 0  | 0x50+0xd0=0x120 | 80+208=288  | 80+-48=32   |
| 1  | 0  | 0  | 1  | 0  | 0  | 0xd0+0x10=0xe0  | 208+16=224  | -48+16=-32  |
| 1  | 0  | 1  | 1  | 0  | 0  | 0xd0+0x50=0x120 | 208+80=288  | -48+80=32   |
| 1  | 1  | 0  | 1  | 0  | 1  | 0xd0+0x90=0x160 | 208+144=352 | -48+-112=96 |
| 1  | 1  | 1  | 1  | 1  | 0  | 0xd0+0xd0=0x1a0 | 208+208=416 | 48+-48=-96  |
|---------------------------------------------------------------------------|
*/

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic1stCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::adc(regs, 0x10);
  EXPECT_EQ(0x60, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic2ndCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::adc(regs, 0x50);
  EXPECT_EQ(0xa0, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(1, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic3rdCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::adc(regs, 0x90);
  EXPECT_EQ(0xe0, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic4thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::adc(regs, 0xd0);
  EXPECT_EQ(0x20, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic5thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::adc(regs, 0x10);
  EXPECT_EQ(0xe0, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic6thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::adc(regs, 0x50);
  EXPECT_EQ(0x20, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic7thCase_MatchTable) {
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::adc(regs, 0x90);
  EXPECT_EQ(0x60, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(1, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, ADC_VerifyOverflowLogic8thCase_MatchTable) {
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::adc(regs, 0xd0);
  EXPECT_EQ(0xa0, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

/*
 SBC Overflow Logic
 source: http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
|--------------|-------------------|---------------------------------------------|
| Input        | Output            | Example                                     |
|--------------|-------------------|---------------------------------------------|
| M7 | N7 | C6 | C7 | B  | S7 | V  | Hex             | Unsigned    | Signed      |
|----|----|----|----|----|----|----|-----------------|-------------|-------------|
| 0  | 1  | 0  | 0  | 1  | 0  | 0  | 0x50-0xf0=0x60  | 80-240=96   | 80--16=96   |
| 0  | 1  | 1  | 0  | 1  | 1  | 1  | 0x50-0xb0=0xa0  | 80-176=160  | 80--80=-96  |
| 0  | 0  | 0  | 0  | 1  | 1  | 0  | 0x50-0x70=0xe0  | 80-112=224  | 80-112=-32  |
| 0  | 0  | 1  | 1  | 0  | 0  | 0  | 0x50-0x30=0x120 | 80-48=32    | 80-48=32    |
| 1  | 1  | 0  | 0  | 1  | 1  | 0  | 0xd0-0xf0=0xe0  | 208-240=224 | -48--16=-32 |
| 1  | 1  | 1  | 1  | 0  | 0  | 0  | 0xd0-0xb0=0x120 | 208-176=32  | -48--80=32  |
| 1  | 0  | 0  | 1  | 0  | 0  | 1  | 0xd0-0x70=0x160 | 208-112=96  | -48-112=96  |
| 1  | 0  | 1  | 1  | 0  | 1  | 0  | 0xd0-0x30=0x1a0 | 208-48=160  | -48-48=-96  |
|--------------------------------------------------------------------------------|
*/

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic1stCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::sbc(regs, 0xf0);
  EXPECT_EQ(0x60, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic2ndCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::sbc(regs, 0xb0);
  EXPECT_EQ(0xa0, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(1, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic3rdCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::sbc(regs, 0x70);
  EXPECT_EQ(0xe0, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic4thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0x50;

  mos6507::sbc(regs, 0x30);
  EXPECT_EQ(0x20, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic5thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::sbc(regs, 0xf0);
  EXPECT_EQ(0xe0, regs.a);
  EXPECT_EQ(0, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic6thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::sbc(regs, 0xb0);
  EXPECT_EQ(0x20, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic7thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::sbc(regs, 0x70);
  EXPECT_EQ(0x60, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(1, regs.ps.overflow);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, SBC_VerifyOverflowLogic8thCase_MatchTable)
{
  mos6507::regs_t regs;
  regs.a = 0xd0;

  mos6507::sbc(regs, 0x30);
  EXPECT_EQ(0xa0, regs.a);
  EXPECT_EQ(1, regs.ps.carry);
  EXPECT_EQ(0, regs.ps.overflow);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, AND_JoinNibbles_ExpectJoinedNibbles)
{
  mos6507::regs_t regs;
  regs.a = 0xf0;

  mos6507::land(regs, 0x0f);
  EXPECT_EQ(0, regs.a);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, AND_AccAndArgWithAllBitsSet_ExpectAllBitsSetWithNegativeFlagSet)
{
  mos6507::regs_t regs;
  regs.a = 0xff;

  mos6507::land(regs, 0xff);
  EXPECT_EQ(0xff, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, AND_AccAndArgWithAllBitsSetExceptMSB_ExpectSameValueWithNegativeFlagNotSet)
{
  mos6507::regs_t regs;
  regs.a = 0x7f;

  mos6507::land(regs, 0x7f);
  EXPECT_EQ(0x7f, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, EOR_AccAndArgWithAllBitsSet_ExpectZero)
{
  mos6507::regs_t regs;
  regs.a = 0xff;

  mos6507::leor(regs, 0xff);
  EXPECT_EQ(0, regs.a);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, ORA_AccAndArgWithAllBitsSet_ExpectAllBitsSetWithNegativeFlag)
{
  mos6507::regs_t regs;
  regs.a = 0xff;

  mos6507::lora(regs, 0xff);
  EXPECT_EQ(0xff, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, ROL_Rotate0x80_Expect0x01)
{
  mos6507::regs_t regs;
  regs.a = 0x80;

  mos6507::rol(regs);
  EXPECT_EQ(0x01, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, ROR_Rotate0x01_Expect0x80)
{
  mos6507::regs_t regs;
  regs.a = 0x01;

  mos6507::ror(regs);
  EXPECT_EQ(0x80, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, SEC_CarryNotSet_CarrySet)
{
  mos6507::regs_t regs;
  regs.ps.carry = 0;

  mos6507::sec(regs);
  EXPECT_EQ(1, regs.ps.carry);
}

TEST (Mos6507_ISA, SEC_CarrySet_CarrySet)
{
  mos6507::regs_t regs;
  regs.ps.carry = 1;

  mos6507::sec(regs);
  EXPECT_EQ(1, regs.ps.carry);
}

TEST (Mos6507_ISA, CLC_CarryNotSet_CarryNotSet)
{
  mos6507::regs_t regs;
  regs.ps.carry = 0;

  mos6507::clc(regs);
  EXPECT_EQ(0, regs.ps.carry);
}

TEST (Mos6507_ISA, CLC_CarrySet_CarryNotSet)
{
  mos6507::regs_t regs;
  regs.ps.carry = 1;

  mos6507::clc(regs);
  EXPECT_EQ(0, regs.ps.carry);
}

TEST (Mos6507_ISA, SED_DecimalNotSet_DecimalSet)
{
  mos6507::regs_t regs;
  regs.ps.decimal = 0;

  mos6507::sed(regs);
  EXPECT_EQ(1, regs.ps.decimal);
}

TEST (Mos6507_ISA, SED_DecimalSet_DecimalSet)
{
  mos6507::regs_t regs;
  regs.ps.decimal = 1;

  mos6507::sed(regs);
  EXPECT_EQ(1, regs.ps.decimal);
}

TEST (Mos6507_ISA, CLD_DecimalNotSet_DecimalNotSet)
{
  mos6507::regs_t regs;
  regs.ps.decimal = 0;

  mos6507::cld(regs);
  EXPECT_EQ(0, regs.ps.decimal);
}

TEST (Mos6507_ISA, CLD_DecimalSet_DecimalNotSet)
{
  mos6507::regs_t regs;
  regs.ps.decimal = 1;

  mos6507::cld(regs);
  EXPECT_EQ(0, regs.ps.decimal);
}

TEST (Mos6507_ISA, SEI_IrqDisableNotSet_IrqDisableSet)
{
  mos6507::regs_t regs;
  regs.ps.irq_disable = 0;

  mos6507::sei(regs);
  EXPECT_EQ(1, regs.ps.irq_disable);
}

TEST (Mos6507_ISA, SEI_IrqDisableSet_IrqDisableSet)
{
  mos6507::regs_t regs;
  regs.ps.irq_disable = 1;

  mos6507::sei(regs);
  EXPECT_EQ(1, regs.ps.irq_disable);
}

TEST (Mos6507_ISA, CLI_IrqDisableSet_IrqDisableNotSet)
{
  mos6507::regs_t regs;
  regs.ps.irq_disable = 0;

  mos6507::cli(regs);
  EXPECT_EQ(0, regs.ps.irq_disable);
}

TEST (Mos6507_ISA, CLI_IrqDisableNotSet_IrqDisableNotSet)
{
  mos6507::regs_t regs;
  regs.ps.irq_disable = 1;

  mos6507::cli(regs);
  EXPECT_EQ(0, regs.ps.irq_disable);
}

TEST (Mos6507_ISA, TAX_CopyPositiveAtoX_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.a = 0x7f;
  regs.x = 0x00;

  mos6507::tax(regs);
  EXPECT_EQ(0x7f, regs.x);
  EXPECT_EQ(regs.x, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TAX_CopyNegativeAtoX_CopiedWithNegativeSet)
{
  mos6507::regs_t regs;
  regs.a = 0x80;
  regs.x = 0x00;

  mos6507::tax(regs);
  EXPECT_EQ(0x80, regs.x);
  EXPECT_EQ(regs.x, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, TAX_CopyZeroAtoX_CopiedWithZeroSet)
{
  mos6507::regs_t regs;
  regs.a = 0x00;
  regs.x = 0xFF;

  mos6507::tax(regs);
  EXPECT_EQ(0x00, regs.x);
  EXPECT_EQ(regs.x, regs.a);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TAY_CopyPositiveAtoY_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.a = 0x7f;
  regs.y = 0x00;

  mos6507::tay(regs);
  EXPECT_EQ(0x7f, regs.y);
  EXPECT_EQ(regs.y, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TAY_CopyNegativeAtoY_CopiedWithNegativeSet)
{
  mos6507::regs_t regs;
  regs.a = 0x80;
  regs.y = 0x00;

  mos6507::tay(regs);
  EXPECT_EQ(0x80, regs.y);
  EXPECT_EQ(regs.y, regs.a);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, TAY_CopyZeroAtoY_CopiedWithZeroSet)
{
  mos6507::regs_t regs;
  regs.a = 0x00;
  regs.y = 0xFF;

  mos6507::tay(regs);
  EXPECT_EQ(0x00, regs.y);
  EXPECT_EQ(regs.y, regs.a);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TXA_CopyPositiveXtoA_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.x = 0x7f;
  regs.a = 0x00;

  mos6507::txa(regs);
  EXPECT_EQ(0x7f, regs.a);
  EXPECT_EQ(regs.a, regs.x);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TXA_CopyNegativeXtoA_CopiedWithNegativeSet)
{
  mos6507::regs_t regs;
  regs.x = 0x80;
  regs.a = 0x00;

  mos6507::txa(regs);
  EXPECT_EQ(0x80, regs.a);
  EXPECT_EQ(regs.a, regs.x);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, TXA_CopyZeroXtoA_CopiedWithZeroSet)
{
  mos6507::regs_t regs;
  regs.x = 0x00;
  regs.a = 0xFF;

  mos6507::txa(regs);
  EXPECT_EQ(0x00, regs.a);
  EXPECT_EQ(regs.a, regs.x);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TYA_CopyPositiveYtoA_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.y = 0x7f;
  regs.a = 0x00;

  mos6507::tya(regs);
  EXPECT_EQ(0x7f, regs.a);
  EXPECT_EQ(regs.a, regs.y);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TYA_CopyNegativeYtoA_CopiedWithNegativeSet)
{
  mos6507::regs_t regs;
  regs.y = 0x80;
  regs.a = 0x00;

  mos6507::tya(regs);
  EXPECT_EQ(0x80, regs.a);
  EXPECT_EQ(regs.a, regs.y);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, TYA_CopyZeroYtoA_CopiedWithZeroSet)
{
  mos6507::regs_t regs;
  regs.y = 0x00;
  regs.a = 0x80;

  mos6507::tya(regs);
  EXPECT_EQ(0x00, regs.a);
  EXPECT_EQ(regs.a, regs.y);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TSX_CopyPositiveStacktoX_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.sp = 0x7f;
  regs.x = 0x00;

  mos6507::tsx(regs);
  EXPECT_EQ(0x7f, regs.x);
  EXPECT_EQ(regs.x, regs.sp);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TSX_CopyNegativeStacktoX_CopiedWithNegativeSet)
{
  mos6507::regs_t regs;
  regs.sp = 0x80;
  regs.x = 0x00;

  mos6507::tsx(regs);
  EXPECT_EQ(0x80, regs.x);
  EXPECT_EQ(regs.x, regs.sp);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(1, regs.ps.negative);
}

TEST (Mos6507_ISA, TSX_CopyZeroStacktoX_CopiedWithZeroSet)
{
  mos6507::regs_t regs;
  regs.sp = 0x00;
  regs.x = 0xFF;

  mos6507::tsx(regs);
  EXPECT_EQ(0x00, regs.x);
  EXPECT_EQ(regs.x, regs.sp);
  EXPECT_EQ(1, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TXS_CopyPositiveXtoStack_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.x = 0x7f;
  regs.sp = 0x00;

  mos6507::txs(regs);
  EXPECT_EQ(0x7f, regs.sp);
  EXPECT_EQ(regs.sp, regs.x);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TXS_CopyNegativeXtoStack_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.x = 0x80;
  regs.sp = 0x00;

  mos6507::txs(regs);
  EXPECT_EQ(0x80, regs.sp);
  EXPECT_EQ(regs.sp, regs.x);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}

TEST (Mos6507_ISA, TXS_CopyZeroXtoStack_CopiedWithNoFlagAffected)
{
  mos6507::regs_t regs;
  regs.x = 0x00;
  regs.sp = 0x80;

  mos6507::txs(regs);
  EXPECT_EQ(0x00, regs.sp);
  EXPECT_EQ(regs.sp, regs.x);
  EXPECT_EQ(0, regs.ps.zero);
  EXPECT_EQ(0, regs.ps.negative);
}
