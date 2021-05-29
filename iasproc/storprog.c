// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "storprog.h"
#include "utils.h"

// Read given program file and load instructions and data to IAS memory
bits16 store_test_programs(IAS *ias, bits16 progoff, bits16 dataoff, char *fname)
{
    // 0-1023 40-bit words be instruction memory
    // 1024-4095 40-bit words be data memory
    FILE *fp = fopen(fname, "r");
    // Converting 40 bit word offset to byte offset
    dataoff = (dataoff * 40) / 8;
    if (fp)
    {
        char buf[256], dummy1[256], dummy2[256];
        bits16 addr;
        bits64 nibbles;
        bits40 bytes;
        // Read program file line-by-line
        while(fgets(buf, 1024, fp) != NULL)
        {
            // Check for HALT instruction
            if(!strcmp(buf, ";HALT"))
            {
                printf("%s", buf);
                progoff += sizeof(bits40);
            }
            // Check for comment line
            else if(buf[0] == ';')
            {
                printf("%s", buf);
            }
            // Check for data load directive
            // Syntax used: LOC <ADDR> DATA <DATABYTES>
            else if(!strncmp(buf, "LOC", 3))
            {
                sscanf(buf, "%s %hd %s %lX", dummy1, &addr, dummy2, &nibbles);
                bytes.content = nibbles & 0x0FFFFFFFFFF;
                printf("%s", buf);
                memcpy(&ias->memory[dataoff], &bytes, sizeof(bits40));
                dataoff += sizeof(bits40);
            }
            // Only other lines allowed are valid IAS instructions in hexadecimal format
            else
            {
                sscanf(buf, "%lX", &nibbles);
                bytes.content = nibbles & 0x0FFFFFFFFFF;
                memcpy(&ias->memory[progoff], &bytes, sizeof(bits40));
                progoff += sizeof(bits40);
            }
        }
    }
    return progoff;
}

