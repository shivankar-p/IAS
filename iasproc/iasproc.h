// This simulator only handles memory operations does not address IO operations

#ifndef __IASPROC_H
#define __IASPROC_H

#include <stdio.h>
#include <string.h>

#define NOP 0
#define LINSTR 1
#define RINSTR 2
#define INSTR 3

#define LOAD_MX 0x01                   // 00000001
#define LOAD_NegMX 0x02                // 00000010
#define LOAD_AbsMX 0x03                // 00000011
#define LOAD_NegOfAbsMX 0x04           // 00000100
#define ADD_MX 0x05                    // 00000101
#define SUB_MX 0x06                    // 00000110
#define ADD_AbsMX 0x07                 // 00000111
#define SUB_AbsMX 0x08                 // 00001000
#define LOAD_MQ_MX 0x09                // 00001001
#define LOAD_MQ 0x0A                   // 00001010
#define MUL_MX 0x0B                    // 00001011
#define DIV_MX 0x0C                    // 00001100
#define JUMP_MX_0_19 0x0D              // 00001101
#define JUMP_MX_20_39 0x0E             // 00001110
#define JUMP_ACNonneg_MX_0_19 0x0F     // 00001111
#define JUMP_ACNonneg_MX_20_39 0x10    // 00010000
#define STOR_MX_8_19 0x12              // 00010010
#define STOR_MX_28_39 0x13             // 00010011
#define LSH 0x14                       // 00010100
#define RSH 0x15                       // 00010101
#define STOR_MX 0x21                   // 00100001

typedef unsigned char bits8;
typedef unsigned short bits16;
typedef unsigned int bits32;
typedef unsigned long int bits64;
// 40 bits data type
typedef struct _bits40 {
    bits64 __attribute__((__packed__)) content : 40;
} bits40;

// Instruction register structure with forced alignment all packed fields
typedef struct _instr_regs {
    bits8  IR;
    bits32 __attribute__((__packed__)) MAR : 12;
    bits32 __attribute__((__packed__)) IBR : 20;
} instr_regs;

// ALU structure with forced alignment all packed fields
typedef struct _ALU {
    bits40 AC;
    bits40 MQ;
    bits40 MBR;
} ALU;

// Control unit structure with forced alignment all packed fields
typedef struct _control_unit {
    bits16 __attribute__((__packed__)) PC : 12;
    instr_regs iregs;
} control_unit;

// CPU structure
typedef struct _CPU {
    control_unit cntl;
    ALU alu;
} CPU;

// IAS structure
typedef struct _IAS {
    CPU cpu;
    bits8 memory[20480];
} IAS;

void run_test_program(IAS *ias, bits16 progoff);

#endif // __IASPROC_H

