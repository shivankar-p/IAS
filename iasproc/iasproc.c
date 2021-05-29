// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "utils.h"

// Fetch cycle
bits16 fetch_instruction(IAS *ias, bits16 progoff)
{
    // Fetch instructions from memory or from IBR
    bits16 nxtoff = 0;
    // Check for next (right) instruction opcode in IBR
    if(ias->cpu.cntl.iregs.IBR)
    {
        // IR <- IBR(0:7)
        ias->cpu.cntl.iregs.IR = (ias->cpu.cntl.iregs.IBR >> 12) & 0x0FF;
        // MAR <- IBR(8:19)
        ias->cpu.cntl.iregs.MAR = ias->cpu.cntl.iregs.IBR & 0x0FFF;
        // Clear IBR once right instruction is fetched
        ias->cpu.cntl.iregs.IBR = 0;
        // Handled right instruction of previous fetch, so no need to increment PC
        nxtoff = progoff;
    }
    // Move to next memopry location to fetch next instructions
    else
    {
        // Set PC to program offset
        ias->cpu.cntl.PC = progoff;
        // MAR <- PC
        ias->cpu.cntl.iregs.MAR = ias->cpu.cntl.PC;
        // MBR <- M(MAR)
        memcpy(&ias->cpu.alu.MBR, &ias->memory[ias->cpu.cntl.iregs.MAR], sizeof(bits40));
        // Check for halt program instruction opcode (0x0000000000)
        if(ias->cpu.alu.MBR.content)
        {
            // Load left instruction opcode into IR
            // IR <- MBR(0:7)
            ias->cpu.cntl.iregs.IR = (ias->cpu.alu.MBR.content >> 32) & 0x0FF;
            // Check if left instruction opcode of fetched set instructions is filled
            if(ias->cpu.cntl.iregs.IR)
            {
                // MAR <- MBR(8:19)
                ias->cpu.cntl.iregs.MAR = (ias->cpu.alu.MBR.content >> 20) & 0x0FFF;
                // IBR <- MBR(20:39)
                ias->cpu.cntl.iregs.IBR = ias->cpu.alu.MBR.content & 0x0FFFFF;
            }
            // If no left instruction, load right instruction to IR, MAR
            else
            {
                // IR <- MBR(20:27)
                ias->cpu.cntl.iregs.IR = ((ias->cpu.alu.MBR.content & 0x0FFFFF) >> 12) & 0x0FF;
                // MAR <- MBR(28:39)
                ias->cpu.cntl.iregs.MAR = (ias->cpu.alu.MBR.content & 0x0FFFFF) & 0x0FFF;
            }
            // Increment PC to point to next memory location
            nxtoff = progoff + sizeof(bits40);
        }
    }
    return nxtoff;
}

// Decode and Execute cycle
void decode_and_execute(IAS *ias, bits8 opcode, bits16 addr, bits16 *nxtoff)
{
    addr = (addr * 40) / 8;
    bits40 value;
    value.content = 0;
    bits64 mulop = 0;
    bits128 mulres = 0;
    // Decode current instruction opcode
    switch(opcode)
    {
        // Execute current decoded instruction
        case ADD_MX:
            // AC <- AC + M(X)
            memcpy(&value, &ias->memory[addr], sizeof(bits40));
            ias->cpu.alu.AC.content += value.content;
            break;
        case SUB_MX:
            // AC <- AC - M(X)
            memcpy(&value, &ias->memory[addr], sizeof(bits40));
            ias->cpu.alu.AC.content -= value.content;
            break;
        case MUL_MX:
            // [AC, MQ] <- AC * M(X)
            memcpy(&mulop, &ias->memory[addr], sizeof(bits40));
            mulres = (bits128)mulop * (bits64)(ias->cpu.alu.AC.content & 0x0FFFFFFFFFFFFFFFF);
            ias->cpu.alu.MQ.content = (mulres & 0x0FFFFFFFFFF);
            ias->cpu.alu.AC.content = ((mulres >> 40) & 0x0FFFFFFFFFF);
            break;
        case DIV_MX:
            // AC <- AC / M(X)
            memcpy(&value, &ias->memory[addr], sizeof(bits40));
            ias->cpu.alu.MQ.content = (ias->cpu.alu.AC.content % value.content);
            ias->cpu.alu.AC.content /= value.content;
            break;
        case LSH:
            // AC <- AC << 1
            ias->cpu.alu.AC.content = ias->cpu.alu.AC.content << 1;
            break;
        case RSH:
            // AC <- AC >> 1
            ias->cpu.alu.AC.content = ias->cpu.alu.AC.content >> 1;
            break;
        case LOAD_MX:
            // AC <- M(X)
            memcpy(&ias->cpu.alu.AC, &ias->memory[addr], sizeof(bits40));
            break;
        case LOAD_MQ:
            // AC <- MQ
            ias->cpu.alu.AC.content = ias->cpu.alu.MQ.content;
            break;
        case STOR_MX:
            // M(x) <- AC
            memcpy(&ias->memory[addr], &ias->cpu.alu.AC, sizeof(bits40));
            break;
        default:
            // Invalid opcode, do nothing
            break;
    }
    return;
}

