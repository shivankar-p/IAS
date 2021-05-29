// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "storprog.h"
#include "utils.h"

void run_test_program(IAS *ias, bits16 progoff)
{
    bits16 nxtoff = 0;
    // Fetch instructions from memory
    nxtoff = fetch_instruction(ias, progoff);
    // Decode and execute left instruction fetched from memory
    decode_and_execute(ias, ias->cpu.cntl.iregs.IR, ias->cpu.cntl.iregs.MAR, &nxtoff);
    while(nxtoff)
    {
        // Fetch instructions from memory
        nxtoff = fetch_instruction(ias, nxtoff);
        // Decode and execute left instruction fetched from memory
        decode_and_execute(ias, ias->cpu.cntl.iregs.IR, ias->cpu.cntl.iregs.MAR, &nxtoff);
    }
    return;
}

int main(int argc, char *argv[])
{
    // Instance of IAS
    IAS ias;
    // Initialize IAS
    memset(&ias, 0, sizeof(IAS));
    // Offsets for program(0 - 1023) and data(1024 - 4095)
    bits16 progoff = 0, dataoff = 1024;

    // Get program file name from command line argument
    char fname[256];
    if (argc > 1)
        strcpy(fname, argv[1]);
    else
        strcpy(fname, "program1");

    // Loading program in memory
    printf("Loading program %s:\n\n", fname);
    store_test_programs(&ias, progoff, dataoff, fname);

    // Run program stored in memory
    printf("\nExecuting program %s ... \n\n", fname);
    run_test_program(&ias, progoff);

    // Displaying contents of 10 output memory locations(1035 to 1044)
    // All test programs use memory locations 1035 to 1044 to store results
    printf("Result:\n\n");
    printf("Memory content at offsets 1035 to 1044:\n");
    for (int idx = 0; idx < 10; idx++)
    {
        printf("M[%d]: ", (1035 + idx));
        print_data(&ias, ((1035 + idx) * 40) / 8, 1);
    }
    return 0;
}

