// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "utils.h"

// Function to print content(40 bits), in hexadecimal format, of given memory location
void print_data(IAS *ias, bits16 off, bits8 rev)
{
    if(rev)
        printf("%2.2X%2.2X%2.2X%2.2X%2.2X\n", (bits8)(0x0FF & ias->memory[off+4]), (bits8)(0x0FF & ias->memory[off+3]), (bits8)(0x0FF & ias->memory[off+2]), (bits8)(0x0FF & ias->memory[off+1]), (bits8)(0x0FF & ias->memory[off]));
    else
        printf("%2.2X%2.2X%2.2X%2.2X%2.2X\n", (bits8)(0x0FF & ias->memory[off]), (bits8)(0x0FF & ias->memory[off+1]), (bits8)(0x0FF & ias->memory[off+2]), (bits8)(0x0FF & ias->memory[off+3]), (bits8)(0x0FF & ias->memory[off+4]));
    return;
}

