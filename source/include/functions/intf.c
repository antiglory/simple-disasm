// intf.c (interface)

#pragma once

#define MEMORY_BOUNDS 1024

void interface() {
    char userInput[24];

    char yOn; // yes or no
    int OOB; // out of bounds

    void (*main_ptr)() = (void*)&main;

    // memory buffer pointer
    uint8_t *memory = (uint8_t *)main_ptr;

    int offset = 0;  // initializing offset
    int RANGE = 0;   // initializing range
    int TEMP_RANGE;  // initializing temporary range
    int TEMP_OFFSET; // initializing temporary offset

    while (1) {
        input(": ", &userInput, 's');

        if (strcmp(userInput, "dump+") == 0) {
            input("", &TEMP_RANGE, 'd');

            if (TEMP_RANGE > MEMORY_BOUNDS) {
                printf("[!] out of bounds\n");
            } else {
                RANGE = TEMP_RANGE;

                for (int i = 0; i < RANGE; i++) {
                    if (offset + i >= MEMORY_BOUNDS) {
                        OOB = 1;
                        printf("[!] out of bounds\n");
                        offset = 1024;
                        break;
                    }

                    printf("    0x%04X          ", (uintptr_t)(memory + offset + i));
                    disasm(memory, offset + i);
                }

                if (OOB != 1) {
                    offset += RANGE;
                    OOB = 0;
                }
            }
        } else if (strcmp(userInput, "dump-") == 0) {
            input("", &RANGE, 'd');

            if (offset - RANGE < 0 || offset == 0 || offset < 0) {
                printf("[!] on 0index\n");
            } else {
                offset -= RANGE; // updating offset
                for (int i = 0; i < RANGE; i++) {
                    printf("    0x%04X          ", (uintptr_t)(memory + offset + i));
                    disasm(memory, offset + i);
                }
            }
        } else if (strcmp(userInput, "acbyte") == 0) {
            printf("%d\n", offset);
        } else if (strcmp(userInput, "goto") == 0) {
            input("", &TEMP_OFFSET, 'd');

            if (TEMP_OFFSET > MEMORY_BOUNDS) {
                printf("[!] out of bounds\n");
            } else {
                offset = TEMP_OFFSET;
                printf("    0x%04X          ", (uintptr_t)(memory + offset));
                disasm(memory, offset);
            }
        } else if (strcmp(userInput, "clear") == 0) {
            input("are you sure? ", &yOn, 'c');

            if (yOn == 'y') {
                system("cls");
            }
        } else if (strcmp(userInput, "exit") == 0) {
            printf("goodbyte!");

            exit(EXIT_SUCCESS);
        } else {
            printf("~ invalid cmd\n");
        }
    }
}