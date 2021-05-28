// This simulator only handles memory operations does not address IO operations

#include "iasproc.h"
#include "storprog.h"
#include "utils.h"

int main()
{
    // Instance of IAS
    IAS ias;
    memset(&ias, 0, sizeof(IAS));
    bits16 progoff = 0, nxtoff = 0;

    nxtoff = store_test_programs(&ias);
    run_test_program(&ias, progoff);
    printf("Data:\n");
    print_data(&ias, (1025 * 40) / 8, 1);
    progoff = nxtoff;
    printf("Next program offset is [%d]\n", (bits16)(progoff * 8));

    return 0;
}

