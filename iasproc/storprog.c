// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "storprog.h"
#include "utils.h"

bits16 store_test_programs(IAS *ias)
{
    // 0-1023 40-bit words be instruction memory
    // 1024-4095 40-bit words be data memory
    bits16 progoff = 0;
    bits16 dataoff = (1024 * 40) / 8;
    instr_40b instr;
    data_40b datum;

    // Program 1
    // Put 0x02BBCCDDEE data in memory location 1024
    // Use 0x0000000000 instruction as HALT to mark end of program
    // ADD M(1024)
    // LSH
    // STOR M(1025)
    // HALT

    // Put 0x0ABBCCDDEE data in memory location 1024
    datum.sbit = 0b0;
    datum.dbits = 0x02BBCCDDEE; // 0b 0000 0010 1011 1011 1100 1100 1101 1101 1110 1110;
    memcpy(ias->memory + dataoff, &datum, sizeof(data_40b));
    dataoff += sizeof(data_40b);
    // ADD M(1024)
    // LSH
    instr.lopcode_8b = 0b00000101;
    instr.laddr_12b = 0b010000000000;
    instr.ropcode_8b = 0b00010100;
    instr.raddr_12b = 0b0;
    memcpy(ias->memory + progoff, &instr, sizeof(instr_40b));
    progoff += sizeof(instr_40b);
    // STOR M(1025)
    instr.lopcode_8b = 0b0;
    instr.laddr_12b = 0b0;
    instr.ropcode_8b = 0b00100001;
    instr.raddr_12b = 0b010000000001;
    memcpy(ias->memory + progoff, &instr, sizeof(instr_40b));
    progoff += sizeof(instr_40b);
    // HALT
    instr.lopcode_8b = 0b0;
    instr.laddr_12b = 0b0;
    instr.ropcode_8b = 0b0;
    instr.raddr_12b = 0b0;
    memcpy(ias->memory + progoff, &instr, sizeof(instr_40b));
    progoff += sizeof(instr_40b);

    printf("Instruction area:\n");
    bits16 off = 0;
    while(off < progoff)
    {
        print_data(ias, off, 1);
        off += sizeof(instr_40b);
    }
    printf("Data area:\n");
    off = (1024 * 40) / 8;
    while(off <= dataoff)
    {
        print_data(ias, off, 1);
        off += sizeof(data_40b);
    }

    return progoff;
}

