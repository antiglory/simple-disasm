#ifndef MAIN_H
#define MAIN_H

// prototypes
int main();
void disasm(uint8_t *buffer, int offset);

#include "../functions/adi.c"
#include "../functions/intf.c"

#include "../functions/modules/disasm.c"

#endif