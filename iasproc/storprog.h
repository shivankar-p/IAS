// This simulator only handles memory operations does not address IO operations

#ifndef __STORPROG_H
#define __STORPROG_H

#include "iasproc.h"

bits16 store_test_programs(IAS *ias, bits16 progoff, bits16 dataoff, char *fname);

#endif // __STORPROG_H

