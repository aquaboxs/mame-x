// license:BSD-3-Clause
// copyright-holders:Ville Linde, Barry Rodewald, Carl, Philip Bennett

#pragma once

#ifndef __CYCLES_H__
#define __CYCLES_H__

struct X86_CYCLE_TABLE
{
	X86_CYCLES op;
	uint8_t cpu_cycles[X86_NUM_CPUS][2];
};

static const X86_CYCLE_TABLE x86_cycle_table[] =
{
	// opcode                     rm/pmode
	//                            i386         i486         pentium      mediagx
	{ CYCLES_MOV_REG_REG,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_REG_MEM,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_MEM_REG,       { {  4,  4 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_IMM_REG,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_IMM_MEM,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_ACC_MEM,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_MEM_ACC,       { {  4,  4 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_MOV_REG_SREG,      { {  2, 18 },  {  3,  3 },  {  2,  2 },  {  1,  6 } }       },
	{ CYCLES_MOV_MEM_SREG,      { {  5, 19 },  {  9,  9 },  {  3,  3 },  {  1,  6 } }       },
	{ CYCLES_MOV_SREG_REG,      { {  2,  2 },  {  3,  3 },  {  1,  1 },  {  1,  6 } }       },
	{ CYCLES_MOV_SREG_MEM,      { {  2,  2 },  {  3,  3 },  {  1,  1 },  {  1,  6 } }       },
	{ CYCLES_MOVSX_REG_REG,     { {  3,  3 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_MOVSX_MEM_REG,     { {  6,  6 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_MOVZX_REG_REG,     { {  3,  3 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_MOVZX_MEM_REG,     { {  6,  6 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_PUSH_RM,           { {  5,  5 },  {  4,  4 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_PUSH_REG_SHORT,    { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_PUSH_SREG,         { {  2,  2 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_PUSH_IMM,          { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_PUSHA,             { { 18, 18 },  { 11, 11 },  {  5,  5 },  { 11, 11 } }       },
	{ CYCLES_POP_RM,            { {  5,  5 },  {  4,  4 },  {  3,  3 },  {  4,  4 } }       },
	{ CYCLES_POP_REG_SHORT,     { {  4,  4 },  {  4,  4 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_POP_SREG,          { {  7, 21 },  {  3,  3 },  {  3,  3 },  {  1,  6 } }       },
	{ CYCLES_POPA,              { { 24, 24 },  {  9,  9 },  {  5,  5 },  {  9,  9 } }       },
	{ CYCLES_XCHG_REG_REG,      { {  3,  3 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_XCHG_REG_MEM,      { {  5,  5 },  {  5,  5 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_IN,                { { 12, 26 },  { 14, 27 },  {  7, 19 },  {  8,  8 } }       },
	{ CYCLES_IN_VAR,            { { 13, 27 },  { 14, 27 },  {  7, 19 },  {  8,  8 } }       },
	{ CYCLES_OUT,               { { 10, 24 },  { 16, 29 },  { 12, 24 },  { 14, 14 } }       },
	{ CYCLES_OUT_VAR,           { { 11, 25 },  { 16, 29 },  { 12, 24 },  { 14, 14 } }       },
	{ CYCLES_LEA,               { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_LDS,               { {  7, 22 },  {  6, 12 },  {  4,  4 },  {  4,  9 } }       },
	{ CYCLES_LES,               { {  7, 22 },  {  6, 12 },  {  4,  4 },  {  4,  9 } }       },
	{ CYCLES_LFS,               { {  7, 22 },  {  6, 12 },  {  4,  4 },  {  4,  9 } }       },
	{ CYCLES_LGS,               { {  7, 22 },  {  6, 12 },  {  4,  4 },  {  4,  9 } }       },
	{ CYCLES_LSS,               { {  7, 22 },  {  6, 12 },  {  4,  4 },  {  4, 10 } }       },
	{ CYCLES_CLC,               { {  2,  2 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_CLD,               { {  2,  2 },  {  2,  2 },  {  2,  2 },  {  4,  4 } }       },
	{ CYCLES_CLI,               { {  8,  8 },  {  5,  5 },  {  7,  7 },  {  6,  6 } }       },
	{ CYCLES_CLTS,              { {  6,  6 },  {  7,  7 },  { 10, 10 },  {  7,  7 } }       },
	{ CYCLES_CMC,               { {  2,  2 },  {  2,  2 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_LAHF,              { {  2,  2 },  {  3,  3 },  {  2,  2 },  {  2,  2 } }       },
	{ CYCLES_POPF,              { {  5,  5 },  {  9,  9 },  {  6,  6 },  {  8,  8 } }       },
	{ CYCLES_PUSHF,             { {  4,  4 },  {  4,  4 },  {  9,  9 },  {  2,  2 } }       },
	{ CYCLES_SAHF,              { {  3,  3 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_STC,               { {  2,  2 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_STD,               { {  2,  2 },  {  2,  2 },  {  2,  2 },  {  4,  4 } }       },
	{ CYCLES_STI,               { {  8,  8 },  {  5,  5 },  {  7,  7 },  {  6,  6 } }       },
	{ CYCLES_ALU_REG_REG,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_ALU_REG_MEM,       { {  7,  7 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_ALU_MEM_REG,       { {  6,  6 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_ALU_IMM_REG,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_ALU_IMM_MEM,       { {  7,  7 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_ALU_IMM_ACC,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_INC_REG,           { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_INC_MEM,           { {  6,  6 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_DEC_REG,           { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_DEC_MEM,           { {  6,  6 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_CMP_REG_REG,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_CMP_REG_MEM,       { {  5,  5 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_CMP_MEM_REG,       { {  6,  6 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_CMP_IMM_REG,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_CMP_IMM_MEM,       { {  5,  5 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_CMP_IMM_ACC,       { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_TEST_REG_REG,      { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_TEST_REG_MEM,      { {  5,  5 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_TEST_IMM_REG,      { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_TEST_IMM_MEM,      { {  5,  5 },  {  2,  2 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_TEST_IMM_ACC,      { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_NEG_REG,           { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_NEG_MEM,           { {  6,  6 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_AAA,               { {  4,  4 },  {  3,  3 },  {  3,  3 },  {  3,  3 } }       },
	{ CYCLES_AAS,               { {  4,  4 },  {  3,  3 },  {  3,  3 },  {  3,  3 } }       },
	{ CYCLES_DAA,               { {  4,  4 },  {  2,  2 },  {  3,  3 },  {  2,  2 } }       },
	{ CYCLES_DAS,               { {  4,  4 },  {  2,  2 },  {  3,  3 },  {  2,  2 } }       },
	{ CYCLES_MUL8_ACC_REG,      { { 17, 17 },  { 13, 13 },  { 11, 11 },  {  4,  4 } }       },
	{ CYCLES_MUL8_ACC_MEM,      { { 20, 20 },  { 13, 13 },  { 11, 11 },  {  4,  4 } }       },
	{ CYCLES_MUL16_ACC_REG,     { { 25, 25 },  { 13, 13 },  { 11, 11 },  {  5,  5 } }       },
	{ CYCLES_MUL16_ACC_MEM,     { { 28, 28 },  { 13, 13 },  { 11, 11 },  {  5,  5 } }       },
	{ CYCLES_MUL32_ACC_REG,     { { 41, 41 },  { 13, 13 },  { 10, 10 },  { 15, 15 } }       },
	{ CYCLES_MUL32_ACC_MEM,     { { 44, 44 },  { 13, 13 },  { 10, 10 },  { 15, 15 } }       },
	{ CYCLES_IMUL8_ACC_REG,     { { 17, 17 },  { 18, 18 },  { 11, 11 },  {  4,  4 } }       },
	{ CYCLES_IMUL8_ACC_MEM,     { { 20, 20 },  { 18, 18 },  { 11, 11 },  {  4,  4 } }       },
	{ CYCLES_IMUL16_ACC_REG,    { { 25, 25 },  { 26, 26 },  { 11, 11 },  {  5,  5 } }       },
	{ CYCLES_IMUL16_ACC_MEM,    { { 28, 28 },  { 26, 26 },  { 11, 11 },  {  5,  5 } }       },
	{ CYCLES_IMUL32_ACC_REG,    { { 41, 41 },  { 42, 42 },  { 10, 10 },  { 15, 15 } }       },
	{ CYCLES_IMUL32_ACC_MEM,    { { 44, 44 },  { 42, 42 },  { 10, 10 },  { 15, 15 } }       },
	{ CYCLES_IMUL8_REG_REG,     { { 17, 17 },  { 13, 13 },  { 10, 10 },  {  4,  4 } }       },
	{ CYCLES_IMUL8_REG_MEM,     { { 20, 20 },  { 13, 13 },  { 10, 10 },  {  4,  4 } }       },
	{ CYCLES_IMUL16_REG_REG,    { { 25, 25 },  { 13, 13 },  { 10, 10 },  {  5,  5 } }       },
	{ CYCLES_IMUL16_REG_MEM,    { { 28, 28 },  { 13, 13 },  { 10, 10 },  {  5,  5 } }       },
	{ CYCLES_IMUL32_REG_REG,    { { 41, 41 },  { 13, 13 },  { 10, 10 },  { 15, 15 } }       },
	{ CYCLES_IMUL32_REG_MEM,    { { 44, 44 },  { 13, 13 },  { 10, 10 },  { 15, 15 } }       },
	{ CYCLES_IMUL16_REG_IMM_REG,{ { 26, 26 },  { 26, 26 },  { 10, 10 },  {  6,  6 } }       },
	{ CYCLES_IMUL16_MEM_IMM_REG,{ { 27, 27 },  { 26, 26 },  { 10, 10 },  {  6,  6 } }       },
	{ CYCLES_IMUL32_REG_IMM_REG,{ { 42, 42 },  { 42, 42 },  { 10, 10 },  { 16, 16 } }       },
	{ CYCLES_IMUL32_MEM_IMM_REG,{ { 43, 43 },  { 42, 42 },  { 10, 10 },  { 16, 16 } }       },
	{ CYCLES_DIV8_ACC_REG,      { { 14, 14 },  { 16, 16 },  { 17, 17 },  { 20, 20 } }       },
	{ CYCLES_DIV8_ACC_MEM,      { { 17, 17 },  { 16, 16 },  { 17, 17 },  { 20, 20 } }       },
	{ CYCLES_DIV16_ACC_REG,     { { 22, 22 },  { 24, 24 },  { 25, 25 },  { 29, 29 } }       },
	{ CYCLES_DIV16_ACC_MEM,     { { 25, 25 },  { 24, 24 },  { 25, 25 },  { 29, 29 } }       },
	{ CYCLES_DIV32_ACC_REG,     { { 38, 38 },  { 40, 40 },  { 41, 41 },  { 45, 45 } }       },
	{ CYCLES_DIV32_ACC_MEM,     { { 41, 41 },  { 40, 40 },  { 41, 41 },  { 45, 45 } }       },
	{ CYCLES_IDIV8_ACC_REG,     { { 19, 19 },  { 19, 19 },  { 22, 22 },  { 20, 20 } }       },
	{ CYCLES_IDIV8_ACC_MEM,     { { 22, 22 },  { 20, 20 },  { 22, 22 },  { 20, 20 } }       },
	{ CYCLES_IDIV16_ACC_REG,    { { 27, 27 },  { 27, 27 },  { 30, 30 },  { 29, 29 } }       },
	{ CYCLES_IDIV16_ACC_MEM,    { { 30, 30 },  { 28, 28 },  { 30, 30 },  { 29, 29 } }       },
	{ CYCLES_IDIV32_ACC_REG,    { { 43, 43 },  { 43, 43 },  { 46, 46 },  { 45, 45 } }       },
	{ CYCLES_IDIV32_ACC_MEM,    { { 46, 46 },  { 44, 44 },  { 46, 46 },  { 45, 45 } }       },
	{ CYCLES_AAD,               { { 19, 19 },  { 14, 14 },  { 10, 10 },  {  7,  7 } }       },
	{ CYCLES_AAM,               { { 17, 17 },  { 15, 15 },  { 18, 18 },  { 19, 19 } }       },
	{ CYCLES_CBW,               { {  3,  3 },  {  3,  3 },  {  3,  3 },  {  3,  3 } }       },
	{ CYCLES_CWD,               { {  2,  2 },  {  3,  3 },  {  2,  2 },  {  2,  2 } }       },
	{ CYCLES_ROTATE_REG,        { {  3,  3 },  {  3,  3 },  {  1,  1 },  {  2,  2 } }       },
	{ CYCLES_ROTATE_MEM,        { {  7,  7 },  {  4,  4 },  {  3,  3 },  {  2,  2 } }       },
	{ CYCLES_ROTATE_CARRY_REG,  { {  9,  9 },  {  8,  8 },  {  7,  7 },  {  8,  8 } }       },
	{ CYCLES_ROTATE_CARRY_MEM,  { { 10, 10 },  {  9,  9 },  {  8,  8 },  {  8,  8 } }       },
	{ CYCLES_SHLD_REG,          { {  3,  3 },  {  2,  2 },  {  4,  4 },  {  3,  3 } }       },
	{ CYCLES_SHLD_MEM,          { {  7,  7 },  {  3,  3 },  {  4,  4 },  {  6,  6 } }       },
	{ CYCLES_SHRD_REG,          { {  3,  3 },  {  2,  2 },  {  4,  4 },  {  3,  3 } }       },
	{ CYCLES_SHRD_MEM,          { {  7,  7 },  {  3,  3 },  {  4,  4 },  {  6,  6 } }       },
	{ CYCLES_NOT_REG,           { {  2,  2 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_NOT_MEM,           { {  6,  6 },  {  3,  3 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_CMPS,              { { 10, 10 },  {  8,  8 },  {  5,  5 },  {  6,  6 } }       },
	{ CYCLES_INS,               { { 15, 29 },  { 17, 30 },  {  9, 22 },  { 11, 11 } }       },
	{ CYCLES_LODS,              { {  5,  5 },  {  5,  5 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_MOVS,              { {  8,  8 },  {  7,  7 },  {  4,  4 },  {  6,  6 } }       },
	{ CYCLES_OUTS,              { { 14, 28 },  { 17, 30 },  { 13, 25 },  { 15, 15 } }       },
	{ CYCLES_SCAS,              { {  8,  8 },  {  6,  6 },  {  4,  4 },  {  2,  2 } }       },
	{ CYCLES_STOS,              { {  5,  5 },  {  5,  5 },  {  3,  3 },  {  2,  2 } }       },
	{ CYCLES_XLAT,              { {  5,  5 },  {  4,  4 },  {  4,  4 },  {  5,  5 } }       },
	{ CYCLES_REP_CMPS_BASE,     { {  5,  5 },  {  0,  0 },  {  0,  0 },  { 11, 11 } }       },
	{ CYCLES_REP_INS_BASE,      { { 14,  8 },  {  0,  0 },  {  0,  0 },  { 17, 17 } }       },
	{ CYCLES_REP_LODS_BASE,     { {  5,  5 },  {  0,  0 },  {  0,  0 },  {  9,  9 } }       },
	{ CYCLES_REP_MOVS_BASE,     { {  8,  8 },  {  0,  0 },  {  0,  0 },  { 12, 12 } }       },
	{ CYCLES_REP_OUTS_BASE,     { { 12,  6 },  {  0,  0 },  {  0,  0 },  { 24, 24 } }       },
	{ CYCLES_REP_SCAS_BASE,     { {  5,  5 },  {  0,  0 },  {  0,  0 },  {  9,  9 } }       },
	{ CYCLES_REP_STOS_BASE,     { {  5,  5 },  {  0,  0 },  {  0,  0 },  {  9,  9 } }       },
	{ CYCLES_REP_CMPS,          { {  5,  5 },  {  8,  8 },  {  5,  5 },  {  4,  4 } }       },
	{ CYCLES_REP_INS,           { { 14,  8 },  { 17, 30 },  {  9, 22 },  {  4,  4 } }       },
	{ CYCLES_REP_LODS,          { {  5,  5 },  {  5,  5 },  {  2,  2 },  {  2,  2 } }       },
	{ CYCLES_REP_MOVS,          { {  8,  8 },  {  7,  7 },  {  4,  4 },  {  2,  2 } }       },
	{ CYCLES_REP_OUTS,          { { 12,  6 },  { 17, 30 },  { 13, 25 },  {  4,  4 } }       },
	{ CYCLES_REP_SCAS,          { {  5,  5 },  {  6,  6 },  {  4,  4 },  {  3,  3 } }       },
	{ CYCLES_REP_STOS,          { {  5,  5 },  {  5,  5 },  {  3,  3 },  {  2,  2 } }       },
	{ CYCLES_BSF_BASE,          { { 11, 11 },  {  6,  6 },  {  6,  6 },  {  4,  4 } }       },
	{ CYCLES_BSF,               { {  3,  3 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_BSR_BASE,          { {  9,  9 },  {  6,  6 },  {  7,  7 },  {  4,  4 } }       },
	{ CYCLES_BSR,               { {  3,  3 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_BT_IMM_REG,        { {  3,  3 },  {  3,  3 },  {  4,  4 },  {  1,  1 } }       },
	{ CYCLES_BT_IMM_MEM,        { {  6,  6 },  {  6,  6 },  {  4,  4 },  {  1,  1 } }       },
	{ CYCLES_BT_REG_REG,        { {  3,  3 },  {  3,  3 },  {  4,  4 },  {  1,  1 } }       },
	{ CYCLES_BT_REG_MEM,        { { 12, 12 },  { 12, 12 },  {  9,  9 },  {  7,  7 } }       },
	{ CYCLES_BTC_IMM_REG,       { {  6,  6 },  {  6,  6 },  {  7,  7 },  {  2,  2 } }       },
	{ CYCLES_BTC_IMM_MEM,       { {  8,  8 },  {  8,  8 },  {  8,  8 },  {  2,  2 } }       },
	{ CYCLES_BTC_REG_REG,       { {  6,  6 },  {  6,  6 },  {  7,  7 },  {  2,  2 } }       },
	{ CYCLES_BTC_REG_MEM,       { { 13, 13 },  { 13, 13 },  { 13, 13 },  {  8,  8 } }       },
	{ CYCLES_BTR_IMM_REG,       { {  6,  6 },  {  6,  6 },  {  7,  7 },  {  2,  2 } }       },
	{ CYCLES_BTR_IMM_MEM,       { {  8,  8 },  {  8,  8 },  {  8,  8 },  {  2,  2 } }       },
	{ CYCLES_BTR_REG_REG,       { {  6,  6 },  {  6,  6 },  {  7,  7 },  {  2,  2 } }       },
	{ CYCLES_BTR_REG_MEM,       { { 13, 13 },  { 13, 13 },  { 13, 13 },  {  8,  8 } }       },
	{ CYCLES_BTS_IMM_REG,       { {  6,  6 },  {  6,  6 },  {  7,  7 },  {  2,  2 } }       },
	{ CYCLES_BTS_IMM_MEM,       { {  8,  8 },  {  8,  8 },  {  8,  8 },  {  2,  2 } }       },
	{ CYCLES_BTS_REG_REG,       { {  6,  6 },  {  6,  6 },  {  7,  7 },  {  2,  2 } }       },
	{ CYCLES_BTS_REG_MEM,       { { 13, 13 },  { 13, 13 },  { 13, 13 },  {  8,  8 } }       },
	{ CYCLES_CALL,              { {  7,  7 },  {  3,  3 },  {  1,  1 },  {  3,  3 } }       },
	{ CYCLES_CALL_REG,          { {  7,  7 },  {  5,  5 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_CALL_MEM,          { { 10, 10 },  {  5,  5 },  {  2,  2 },  {  4,  4 } }       },
	{ CYCLES_CALL_INTERSEG,     { { 17, 34 },  { 18, 20 },  {  4, 13 },  {  9, 14 } }       },
	{ CYCLES_CALL_REG_INTERSEG, { { 22, 38 },  { 17, 20 },  {  4, 14 },  { 11, 15 } }       },
	{ CYCLES_CALL_MEM_INTERSEG, { { 22, 38 },  { 17, 20 },  {  4, 14 },  { 11, 15 } }       },
	{ CYCLES_JMP_SHORT,         { {  7,  7 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_JMP,               { {  7,  7 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_JMP_REG,           { {  7,  7 },  {  5,  5 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_JMP_MEM,           { { 10, 10 },  {  5,  5 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_JMP_INTERSEG,      { { 12, 27 },  { 17, 19 },  {  3,  3 },  {  8, 12 } }       },
	{ CYCLES_JMP_REG_INTERSEG,  { { 17, 31 },  { 13, 18 },  {  4,  4 },  { 10, 10 } }       },
	{ CYCLES_JMP_MEM_INTERSEG,  { { 17, 31 },  { 13, 18 },  {  4,  4 },  { 10, 13 } }       },
	{ CYCLES_RET,               { { 10, 10 },  {  5,  5 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_RET_IMM,           { { 10, 10 },  {  5,  5 },  {  2,  2 },  {  3,  3 } }       },
	{ CYCLES_RET_INTERSEG,      { { 18, 32 },  { 13, 13 },  {  4,  4 },  { 10, 13 } }       },
	{ CYCLES_RET_IMM_INTERSEG,  { { 18, 32 },  { 14, 14 },  {  4,  4 },  { 10, 13 } }       },
	{ CYCLES_JCC_DISP8,         { {  7,  7 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_JCC_FULL_DISP,     { {  7,  7 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_JCC_DISP8_NOBRANCH,{ {  3,  3 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_JCC_FULL_DISP_NOBRANCH,{ {  3,  3 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_JCXZ,              { {  9,  9 },  {  1,  1 },  {  1,  1 },  {  2,  2 } }       },
	{ CYCLES_JCXZ_NOBRANCH,     { {  5,  5 },  {  1,  1 },  {  1,  1 },  {  2,  2 } }       },
	{ CYCLES_LOOP,              { { 11, 11 },  {  6,  6 },  {  5,  5 },  {  2,  2 } }       },
	{ CYCLES_LOOPZ,             { { 11, 11 },  {  9,  9 },  {  8,  8 },  {  2,  2 } }       },
	{ CYCLES_LOOPNZ,            { { 11, 11 },  {  9,  9 },  {  8,  8 },  {  2,  2 } }       },
	{ CYCLES_SETCC_REG,         { {  4,  4 },  {  3,  3 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_SETCC_MEM,         { {  5,  5 },  {  4,  4 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_ENTER,             { { 10, 10 },  { 14, 14 },  { 11, 11 },  { 13, 13 } }       },
	{ CYCLES_LEAVE,             { {  4,  4 },  {  5,  5 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_INT,               { { 37, 37 },  { 30, 30 },  { 16, 16 },  { 19, 19 } }       },
	{ CYCLES_INT3,              { { 33, 33 },  { 26, 26 },  { 13, 13 },  { 19, 19 } }       },
	{ CYCLES_INTO_OF1,          { { 35, 35 },  { 28, 28 },  { 13, 13 },  { 19, 19 } }       },
	{ CYCLES_INTO_OF0,          { {  3,  3 },  {  3,  3 },  {  4,  4 },  {  4,  4 } }       },
	{ CYCLES_BOUND_IN_RANGE,    { { 10, 10 },  {  7,  7 },  {  8,  8 },  {  7,  7 } }       },
	{ CYCLES_BOUND_OUT_RANGE,   { { 44, 44 },  {  7,  7 },  {  8,  8 },  {  8,  8 } }       },
	{ CYCLES_IRET,              { { 22, 22 },  { 15, 15 },  {  8,  8 },  { 13, 13 } }       },
	{ CYCLES_HLT,               { {  5,  5 },  {  4,  4 },  {  4,  4 },  { 10, 10 } }       },
	{ CYCLES_MOV_REG_CR0,       { { 11, 11 },  { 16, 16 },  { 16, 16 },  { 20, 18 } }       },
	{ CYCLES_MOV_REG_CR2,       { {  4,  4 },  {  4,  4 },  {  4,  4 },  {  5,  5 } }       },
	{ CYCLES_MOV_REG_CR3,       { {  5,  5 },  {  4,  4 },  {  4,  4 },  {  5,  6 } }       },
	{ CYCLES_MOV_CR_REG,        { {  6,  6 },  {  4,  4 },  {  4,  4 },  {  6,  6 } }       },
	{ CYCLES_MOV_REG_DR0_3,     { { 22, 22 },  { 10, 10 },  { 10, 10 },  { 10, 10 } }       },
	{ CYCLES_MOV_REG_DR6_7,     { { 16, 16 },  { 10, 10 },  { 10, 10 },  { 10, 10 } }       },
	{ CYCLES_MOV_DR6_7_REG,     { { 14, 14 },  { 11, 11 },  { 11, 11 },  {  9,  9 } }       },
	{ CYCLES_MOV_DR0_3_REG,     { { 22, 22 },  { 11, 11 },  { 11, 11 },  {  9,  9 } }       },
	{ CYCLES_MOV_REG_TR6_7,     { { 12, 12 },  {  4,  4 },  {  4,  4 },  { 11, 11 } }       },
	{ CYCLES_MOV_TR6_7_REG,     { { 12, 12 },  {  3,  3 },  {  3,  3 },  {  3,  3 } }       },
	{ CYCLES_NOP,               { {  3,  3 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_WAIT,              { {  7,  7 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_ARPL_REG,          { {  0, 20 },  {  0,  9 },  {  0,  7 },  {  0,  9 } }       },
	{ CYCLES_ARPL_MEM,          { {  0, 21 },  {  0,  9 },  {  0,  7 },  {  0,  9 } }       },
	{ CYCLES_LAR_REG,           { {  0, 15 },  { 11, 11 },  {  8,  8 },  {  0,  9 } }       },
	{ CYCLES_LAR_MEM,           { {  0, 16 },  { 11, 11 },  {  8,  8 },  {  0,  9 } }       },
	{ CYCLES_LGDT,              { { 11, 11 },  { 11, 11 },  {  6,  6 },  { 10, 10 } }       },
	{ CYCLES_LIDT,              { { 11, 11 },  { 11, 11 },  {  6,  6 },  { 10, 10 } }       },
	{ CYCLES_LLDT_REG,          { {  0, 20 },  { 11, 11 },  {  9,  9 },  {  0,  8 } }       },
	{ CYCLES_LLDT_MEM,          { {  0, 24 },  { 11, 11 },  {  9,  9 },  {  0,  8 } }       },
	{ CYCLES_LMSW_REG,          { { 11, 11 },  { 13, 13 },  {  8,  8 },  { 11, 11 } }       },
	{ CYCLES_LMSW_MEM,          { { 14, 14 },  { 13, 13 },  {  8,  8 },  { 11, 11 } }       },
	{ CYCLES_LSL_REG,           { {  0, 21 },  { 10, 10 },  {  8,  8 },  {  0,  9 } }       },
	{ CYCLES_LSL_MEM,           { {  0, 22 },  { 10, 10 },  {  8,  8 },  {  0,  9 } }       },
	{ CYCLES_LTR_REG,           { {  0, 23 },  { 20, 20 },  { 10, 10 },  {  0,  9 } }       },
	{ CYCLES_LTR_MEM,           { {  0, 27 },  { 20, 20 },  { 10, 10 },  {  0,  9 } }       },
	{ CYCLES_SGDT,              { {  9,  9 },  { 10, 10 },  {  4,  4 },  {  6,  6 } }       },
	{ CYCLES_SIDT,              { {  9,  9 },  { 10, 10 },  {  4,  4 },  {  6,  6 } }       },
	{ CYCLES_SLDT_REG,          { {  0,  2 },  {  2,  2 },  {  2,  2 },  {  0,  1 } }       },
	{ CYCLES_SLDT_MEM,          { {  0,  2 },  {  3,  3 },  {  2,  2 },  {  0,  1 } }       },
	{ CYCLES_SMSW_REG,          { {  2,  2 },  {  2,  2 },  {  4,  4 },  {  4,  4 } }       },
	{ CYCLES_SMSW_MEM,          { {  2,  2 },  {  3,  3 },  {  4,  4 },  {  4,  4 } }       },
	{ CYCLES_STR_REG,           { {  0,  2 },  {  2,  2 },  {  2,  2 },  {  0,  3 } }       },
	{ CYCLES_STR_MEM,           { {  0,  2 },  {  3,  3 },  {  2,  2 },  {  0,  3 } }       },
	{ CYCLES_VERR_REG,          { {  0, 10 },  { 11, 11 },  {  7,  7 },  {  0,  8 } }       },
	{ CYCLES_VERR_MEM,          { {  0, 11 },  { 11, 11 },  {  7,  7 },  {  0,  8 } }       },
	{ CYCLES_VERW_REG,          { {  0, 15 },  { 11, 11 },  {  7,  7 },  {  0,  8 } }       },
	{ CYCLES_VERW_MEM,          { {  0, 16 },  { 11, 11 },  {  7,  7 },  {  0,  8 } }       },
	{ CYCLES_LOCK,              { {  0,  0 },  {  1,  1 },  {  1,  1 },  {  1,  1 } }       },

	// i486+
	{ CYCLES_BSWAP,             { {  0,  0 },  {  1,  1 },  {  1,  1 },  {  6,  6 } }       },
	{ CYCLES_CMPXCHG,           { {  0,  0 },  {  6,  6 },  {  5,  5 },  {  6,  6 } }       },
	{ CYCLES_INVD,              { {  0,  0 },  {  4,  4 },  { 15, 15 },  { 20, 20 } }       },
	{ CYCLES_XADD,              { {  0,  0 },  {  4,  4 },  {  4,  4 },  {  2,  2 } }       },

	// Pentium+
	{ CYCLES_CMPXCHG8B,         { {  0,  0 },  {  0,  0 },  { 10, 10 },  {  6,  6 } }       },
	{ CYCLES_CPUID,             { {  0,  0 },  {  0,  0 },  { 14, 14 },  { 12, 12 } }       },
	{ CYCLES_CPUID_EAX1,        { {  0,  0 },  {  0,  0 },  { 14, 14 },  { 12, 12 } }       },
	{ CYCLES_RDTSC,             { {  0,  0 },  {  0,  0 },  { 20, 20 },  {  1,  1 } }       },
	{ CYCLES_RSM,               { {  0,  0 },  {  0,  0 },  { 82, 82 },  { 57, 57 } }       },
	{ CYCLES_RDMSR,             { {  0,  0 },  {  0,  0 },  { 20, 20 },  {  1,  1 } }       },

	// FPU
	{ CYCLES_FABS,              { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FADD,              { {  0,  0 },  {  8,  8 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_FBLD,              { {  0,  0 },  { 70, 70 },  { 48, 48 },  {  1,  1 } }       },
	{ CYCLES_FBSTP,             { {  0,  0 },  {172,172 },  {148,148 },  {  1,  1 } }       },
	{ CYCLES_FCHS,              { {  0,  0 },  {  6,  6 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FCLEX,             { {  0,  0 },  {  7,  7 },  {  9,  9 },  {  1,  1 } }       },
	{ CYCLES_FCOM,              { {  0,  0 },  {  4,  4 },  {  4,  4 },  {  1,  1 } }       },
	{ CYCLES_FCOS,              { {  0,  0 },  {255,255 },  {124,124 },  {  1,  1 } }       },
	{ CYCLES_FDECSTP,           { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FDISI,             { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FDIV,              { {  0,  0 },  { 73, 73 },  { 39, 39 },  {  1,  1 } }       },
	{ CYCLES_FDIVR,             { {  0,  0 },  { 73, 73 },  { 39, 39 },  {  1,  1 } }       },
	{ CYCLES_FENI,              { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FFREE,             { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FIADD,             { {  0,  0 },  { 20, 20 },  {  7,  7 },  {  1,  1 } }       },
	{ CYCLES_FICOM,             { {  0,  0 },  { 16, 16 },  {  8,  8 },  {  1,  1 } }       },
	{ CYCLES_FIDIV,             { {  0,  0 },  { 85, 85 },  { 42, 42 },  {  1,  1 } }       },
	{ CYCLES_FILD,              { {  0,  0 },  { 13, 13 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_FIMUL,             { {  0,  0 },  { 23, 23 },  {  7,  7 },  {  1,  1 } }       },
	{ CYCLES_FINCSTP,           { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FINIT,             { {  0,  0 },  { 17, 17 },  { 16, 16 },  {  1,  1 } }       },
	{ CYCLES_FIST,              { {  0,  0 },  { 29, 29 },  {  6,  6 },  {  1,  1 } }       },
	{ CYCLES_FISUB,             { {  0,  0 },  { 20, 20 },  {  7,  7 },  {  1,  1 } }       },
	{ CYCLES_FLD,               { {  0,  0 },  {  4,  4 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FLDZ,              { {  0,  0 },  {  4,  4 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_FLD1,              { {  0,  0 },  {  4,  4 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_FLDL2E,            { {  0,  0 },  {  8,  8 },  {  5,  5 },  {  1,  1 } }       },
	{ CYCLES_FLDL2T,            { {  0,  0 },  {  8,  8 },  {  5,  5 },  {  1,  1 } }       },
	{ CYCLES_FLDLG2,            { {  0,  0 },  {  8,  8 },  {  5,  5 },  {  1,  1 } }       },
	{ CYCLES_FLDLN2,            { {  0,  0 },  {  8,  8 },  {  5,  5 },  {  1,  1 } }       },
	{ CYCLES_FLDPI,             { {  0,  0 },  {  8,  8 },  {  5,  5 },  {  1,  1 } }       },
	{ CYCLES_FLDCW,             { {  0,  0 },  {  4,  4 },  {  7,  7 },  {  1,  1 } }       },
	{ CYCLES_FLDENV,            { {  0,  0 },  { 44, 44 },  { 37, 37 },  {  1,  1 } }       },
	{ CYCLES_FMUL,              { {  0,  0 },  { 16, 16 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_FNOP,              { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FPATAN,            { {  0,  0 },  {218,218 },  {173,173 },  {  1,  1 } }       },
	{ CYCLES_FPREM,             { {  0,  0 },  { 70, 70 },  { 16, 16 },  {  1,  1 } }       },
	{ CYCLES_FPREM1,            { {  0,  0 },  { 72, 72 },  { 20, 20 },  {  1,  1 } }       },
	{ CYCLES_FPTAN,             { {  0,  0 },  {200,200 },  {173,173 },  {  1,  1 } }       },
	{ CYCLES_FRNDINT,           { {  0,  0 },  { 21, 21 },  {  9,  9 },  {  1,  1 } }       },
	{ CYCLES_FRSTOR,            { {  0,  0 },  {131,131 },  { 75, 75 },  {  1,  1 } }       },
	{ CYCLES_FSAVE,             { {  0,  0 },  {154,154 },  {127,127 },  {  1,  1 } }       },
	{ CYCLES_FSCALE,            { {  0,  0 },  { 30, 30 },  { 20, 20 },  {  1,  1 } }       },
	{ CYCLES_FSETPM,            { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FSIN,              { {  0,  0 },  {255,255 },  {126,126 },  {  1,  1 } }       },
	{ CYCLES_FSINCOS,           { {  0,  0 },  {255,255 },  {137,137 },  {  1,  1 } }       },
	{ CYCLES_FSQRT,             { {  0,  0 },  { 83, 83 },  { 70, 70 },  {  1,  1 } }       },
	{ CYCLES_FST,               { {  0,  0 },  {  3,  3 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FSTCW,             { {  0,  0 },  {  3,  3 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_FSTENV,            { {  0,  0 },  { 67, 67 },  { 48, 48 },  {  1,  1 } }       },
	{ CYCLES_FSTSW,             { {  0,  0 },  {  3,  3 },  {  2,  2 },  {  1,  1 } }       },
	{ CYCLES_FSUB,              { {  0,  0 },  {  8,  8 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_FSUBR,             { {  0,  0 },  {  8,  8 },  {  3,  3 },  {  1,  1 } }       },
	{ CYCLES_FTST,              { {  0,  0 },  {  4,  4 },  {  4,  4 },  {  1,  1 } }       },
	{ CYCLES_FUCOM,             { {  0,  0 },  {  4,  4 },  {  4,  4 },  {  1,  1 } }       },
	{ CYCLES_FXAM,              { {  0,  0 },  {  8,  8 },  { 21, 21 },  {  1,  1 } }       },
	{ CYCLES_FXCH,              { {  0,  0 },  {  4,  4 },  {  1,  1 },  {  1,  1 } }       },
	{ CYCLES_FXTRACT,           { {  0,  0 },  { 16, 16 },  { 13, 13 },  {  1,  1 } }       },
	{ CYCLES_FYL2X,             { {  0,  0 },  {196,196 },  {111,111 },  {  1,  1 } }       },
	{ CYCLES_FYL2XPI,           { {  0,  0 },  {171,171 },  {103,103 },  {  1,  1 } }       },
	{ CYCLES_CMPXCHG_REG_REG_T, { {  0,  0 },  {  6,  6 },  {  6,  6 },  {  6,  6 } }       },
	{ CYCLES_CMPXCHG_REG_REG_F, { {  0,  0 },  {  9,  9 },  {  9,  9 },  {  9,  9 } }       },
	{ CYCLES_CMPXCHG_REG_MEM_T, { {  0,  0 },  {  7,  7 },  {  7,  7 },  {  7,  7 } }       },
	{ CYCLES_CMPXCHG_REG_MEM_F, { {  0,  0 },  { 10, 10 },  { 10, 10 },  { 10, 10 } }       },
};

#endif /* __CYCLES_H__ */