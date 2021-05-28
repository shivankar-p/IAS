// This simulator only handles memory operations does not address IO operations

#ifndef __UTILS_H
#define __UTILS_H

#include "iasproc.h"

// Instruction register structure with forced alignment all packed fields
typedef struct _instr_40b {
    // IBR : 20 bits ropcode_8b:raddr_12b
    // raddr_12b : 12 bits
    bits32 __attribute__((__packed__)) raddr_12b : 12;
    // ropcode_8b : 8 bits
    bits32 __attribute__((__packed__)) ropcode_8b : 8;
    // MAR : 12 bits
    bits32 __attribute__((__packed__)) laddr_12b : 12;
    // IR : 8 bits
    bits8  lopcode_8b;
} instr_40b;

// Data structure with forced alignment all packed fields
typedef struct _data_40b {
    bits64 __attribute__((__packed__)) dbits : 39;
    bits64 __attribute__((__packed__)) sbit : 1;
} data_40b;

void print_instruction(instr_40b instr, bits8 flag);
void print_data(IAS *ias, bits16 off, bits8 rev);

#endif // __UTILS_H

