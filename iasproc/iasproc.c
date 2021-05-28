// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "utils.h"

void decode_and_execute(IAS *ias, bits8 opcode, bits16 addr)
{
    addr = (addr * 40) / 8;
    switch(opcode)
    {
        case ADD_MX:
            memcpy(&ias->cpu.alu.AC, ias->memory + addr, sizeof(bits40));
            break;
        case LSH:
            ias->cpu.alu.AC.content = ias->cpu.alu.AC.content * 2;
            break;
        case STOR_MX:
            memcpy(ias->memory + addr, &ias->cpu.alu.AC, sizeof(bits40));
            break;
        default:
            break;
    }
    return;
}

void run_test_program(IAS *ias, bits16 progoff)
{
    // Fetch instructions from memory
    ias->cpu.cntl.PC = progoff;
    ias->cpu.cntl.iregs.MAR = ias->cpu.cntl.PC;
    memcpy(&ias->cpu.alu.MBR, &ias->memory[ias->cpu.cntl.iregs.MAR], sizeof(bits40));
    while(ias->cpu.alu.MBR.content)
    {
        printf("MBR [%lX]\n", (bits64)(ias->cpu.alu.MBR.content));
        ias->cpu.cntl.iregs.IR = (ias->cpu.alu.MBR.content >> 32) & 0x0FF;
        printf("IR [%X]\n", ias->cpu.cntl.iregs.IR);
        if(ias->cpu.cntl.iregs.IR)
        {
            ias->cpu.cntl.iregs.MAR = (ias->cpu.alu.MBR.content >> 20) & 0x0FFF;
            printf("MAR [%X]\n", ias->cpu.cntl.iregs.MAR);
            ias->cpu.cntl.iregs.IBR = ias->cpu.alu.MBR.content & 0x0FFFFF;
            printf("IBR [%X]\n", ias->cpu.cntl.iregs.IBR);
            // Decode and execute left instruction fetched from memory
            decode_and_execute(ias, ias->cpu.cntl.iregs.IR, ias->cpu.cntl.iregs.MAR);
            ias->cpu.cntl.iregs.IR = (ias->cpu.cntl.iregs.IBR >> 12) & 0x0FF;
            ias->cpu.cntl.iregs.MAR = ias->cpu.cntl.iregs.IBR & 0x0FFF;
        }
        else
        {
            ias->cpu.cntl.iregs.IR = ((ias->cpu.alu.MBR.content & 0x0FFFFF) >> 12) & 0x0FF;
            ias->cpu.cntl.iregs.MAR = (ias->cpu.alu.MBR.content & 0x0FFFFF) & 0x0FFF;
        }
        // Decode and execute right instruction fetched from memory
        decode_and_execute(ias, ias->cpu.cntl.iregs.IR, ias->cpu.cntl.iregs.MAR);
        ias->cpu.cntl.PC += sizeof(bits40);
        ias->cpu.cntl.iregs.MAR = ias->cpu.cntl.PC;
        memcpy(&ias->cpu.alu.MBR, &ias->memory[ias->cpu.cntl.iregs.MAR], sizeof(bits40));
    }
    return;
}

