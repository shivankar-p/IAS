// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "utils.h"

void print_instruction(instr_40b instr, bits8 flag)
{
    if (flag & LINSTR)
        printf("Instruction lopcode [%2.2X], laddr [%2.2X]\n", (bits8)(0x0FF & instr.lopcode_8b), (bits16)(0x0FFF & instr.laddr_12b));
    if (flag & RINSTR)
        printf("Instruction ropcode [%2.2X], raddr [%2.2X]\n", (bits8)(0x0FF & instr.ropcode_8b), (bits16)(0x0FFF & instr.raddr_12b));
    return;
}

void print_data(IAS *ias, bits16 off, bits8 rev)
{
    if(rev)
        printf("[%2.2X][%2.2X][%2.2X][%2.2X][%2.2X]\n", (bits8)(0x0FF & ias->memory[off+4]), (bits8)(0x0FF & ias->memory[off+3]), (bits8)(0x0FF & ias->memory[off+2]), (bits8)(0x0FF & ias->memory[off+1]), (bits8)(0x0FF & ias->memory[off]));
    else
        printf("[%2.2X][%2.2X][%2.2X][%2.2X][%2.2X]\n", (bits8)(0x0FF & ias->memory[off]), (bits8)(0x0FF & ias->memory[off+1]), (bits8)(0x0FF & ias->memory[off+2]), (bits8)(0x0FF & ias->memory[off+3]), (bits8)(0x0FF & ias->memory[off+4]));
    return;
}

