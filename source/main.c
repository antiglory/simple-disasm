// this is very noisy, in some scenarios, the detection capacity is considerable

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "include/functions/modules/disasm.c"
#include "include/functions/adi.c"
#include "include/functions/help.c"
#include "include/functions/handlers.c"

#define MEMORY_LIMIT 2048 // i preferred to add a limit that the user can dump, but you can remove
#define MAX_SEGMENT_SIZE 8192 // i also added a limit for reading the segment, but you can remove it too

// prototypes
int main();
uintptr_t GetCodeSegmentBaseAddress(); /* this is a branch of an old version, i chose to leave it in the program, but if 
                                          removed it will not interfere with its functioning */

// global vars
uintptr_t SegmentBaseAddress = 0;
pid_t GlobalProcessId = 0;

uintptr_t GetCodeSegmentBaseAddress() {
    uintptr_t codeSegmentBaseAddress = 0;

    char mapsFilePath[256];
    FILE *mapsFile;
    char line[256];

    if (GlobalProcessId == 0) {
        return 1;
    }
    sprintf(mapsFilePath, "/proc/%d/maps", GlobalProcessId);

    mapsFile = fopen(mapsFilePath, "r");
    if (!mapsFile) {
        return 2;
    }

    while (fgets(line, sizeof(line), mapsFile)) {
        if (strstr(line, "[stack]") != NULL) {
            sscanf(line, "%lx-", &codeSegmentBaseAddress);
            break;
        }
    }

    fclose(mapsFile);
    return codeSegmentBaseAddress;
}

char* GetCodeSegment() {
    char proc_path[50];
    sprintf(proc_path, "/proc/%d/maps", GlobalProcessId);

    FILE* maps_file = fopen(proc_path, "r");
    if (maps_file == NULL) {
        perror("[!] error launching process maps\n");
        return NULL;
    }

    char* buffer = (char*)malloc(MAX_SEGMENT_SIZE);
    if (buffer == NULL) {
        perror("[!] error allocating memory to buffer\n");
        fclose(maps_file);
        return NULL;
    }

    // saving base address
    void* code_start_address = NULL;

    // reading process maps
    char line[256];
    while (fgets(line, sizeof(line), maps_file) != NULL) {
        if (strstr(line, "r-xp") != NULL) {
            sscanf(line, "%lx", &code_start_address);
            break;
        }
    }

    fclose(maps_file);

    if (code_start_address == NULL) {
        fprintf(stderr, "[!] cannot find process code segment\n");
        free(buffer);
        return NULL;
    }

    sprintf(proc_path, "/proc/%d/mem", GlobalProcessId);
    FILE* mem_file = fopen(proc_path, "rb");
    if (mem_file == NULL) {
        perror("[!] error reading process memory by maps\n");
        free(buffer);
        return NULL;
    }

    // moving file memory pointer to the top of the code segment
    if (fseek(mem_file, (long)code_start_address, SEEK_SET) != 0) {
        perror("[!] error positioning maps pointer\n");
        fclose(mem_file);
        free(buffer);
        return NULL;
    }

    // reading code segment to buffer
    ssize_t bytes_read = fread(buffer, 1, MAX_SEGMENT_SIZE, mem_file);
    if (bytes_read < 0) {
        perror("[!] some error ocurred reading process code segment\n");
        fclose(mem_file);
        free(buffer);
        return NULL;
    }

    fclose(mem_file);

    return buffer;
}

void Setup() {
    char userInput[24]; // user input to setup

    while (1) {
        input("+ ", &userInput, 's');

        if (strcmp(userInput, "set") == 0) {
            input("", &userInput, 's');
            if (strcmp(userInput, "base_address") == 0) {
                input("", &SegmentBaseAddress, 'a');
            } else if (strcmp(userInput, "process_id") == 0) {
                input("", &GlobalProcessId, 'p');
            } else {
                printf("~ invalid operation\n");
            }
        } else if (strcmp(userInput, "get") == 0) {
            input("", &userInput, 's');

            uintptr_t GetCodeSegmentBaseAddressVar = GetCodeSegmentBaseAddress();
            if (GetCodeSegmentBaseAddressVar == 1) {
                printf("[!] pid was not set\n");
            } else if (GetCodeSegmentBaseAddressVar == 2) {
                printf("[!] failed to find (did you set the correct pid?)\n");
            } else if (strcmp(userInput, "base_address") == 0) {
                printf("[=] %u\n", GetCodeSegmentBaseAddressVar);
            } else {
                printf("~ invalid argument\n");
            }
        } else if (strcmp(userInput, "find") == 0) {
            input("", &userInput, 's');

            if (strcmp(userInput, "process_id") == 0) {
                printf("[=] %u\n", GlobalProcessId);
            } else if (strcmp(userInput, "base_address") == 0) {
                printf("[=] %u\n", SegmentBaseAddress);
            } else {
                printf("~ invalid argument\n");
            }
        } else if (strcmp(userInput, "help") == 0) {
            printHelp();
        } else if (strcmp(userInput, "done") == 0) {
            if (GlobalProcessId != 0 && SegmentBaseAddress != 0) {
                printf("\n[+] loading and calling interface\n");
                ProgramInterface();
            } else {
                input("missing values, are you sure? ", userInput, 's');
                    if (strcmp(userInput, "y") == 0) {
                        printf("\n[+] loading and calling interface\n");
                        ProgramInterface();
                    }
            }
        } else if (strcmp(userInput, "abort") == 0) {
            printf("[-] aborting\n");
            exit(EXIT_SUCCESS); // success?
        } else {
            printf("?\n");
        }
    }
}

void ProgramInterface() {
    signal(SIGSEGV, segfault_handler); // acontece

    uintptr_t *memory = (uintptr_t *)GetCodeSegment(); // buffer pointer to manipulate each byte individually

    char userInput[24]; // user input to interface

    int offset = 0; // segment offset
    int RANGE = 0; // range which will be reached

    int TEMP_RANGE;  // temporary range
    int TEMP_OFFSET; // temporary offset

    int OOB; // out of bounds, defined in MEMORY_LIMIT macro

    while (1) {
        input(": ", &userInput, 's');

        if (strcmp(userInput, "dump+") == 0) {
            input("", &TEMP_RANGE, 'd');

            if (userInput < 0) {
                printf("always be positive, always.\n");
            }

            if (TEMP_RANGE > MEMORY_LIMIT) {
                printf("[!] out of bounds\n");
            } else {
                RANGE = TEMP_RANGE;

                for (int i = 0; i < RANGE; i++) {
                    if (offset + i >= MEMORY_LIMIT) {
                        OOB = 1;
                        printf("[!] out of bounds\n");
                        offset = MEMORY_LIMIT;
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
        } else if (strcmp(userInput, "find") == 0) {
            input("", &userInput, 's');
            if (strcmp(userInput, "buffer") == 0) {
                input("", userInput, 's');
                if (strcmp(userInput, "limit") == 0) {
                    printf("[=] %ld\n", MEMORY_LIMIT);
                }
            }
        } else if (strcmp(userInput, "offset") == 0) {
            printf("%d\n", offset);
        } else if (strcmp(userInput, "goto") == 0) {
            input("", &TEMP_OFFSET, 'd');

            if (TEMP_OFFSET > MEMORY_LIMIT) {
                printf("[!] out of bounds\n");
            } else {
                offset = TEMP_OFFSET;
                printf("    0x%04X          ", (uintptr_t)(memory + offset));
                disasm(memory, offset);
            }
        } else if (strcmp(userInput, "help") == 0) {
            printHelp();
        }
        else if (strcmp(userInput, "clear") == 0) {
            input("are you sure? ", &userInput, 's');

            if (strcmp(userInput, "y") == 0) {
                system("clear");
            }
        } else if (strcmp(userInput, "exit") == 0) {
            printf("+0 goodbyte!");

            exit(EXIT_SUCCESS);
        } else {
            printf("~ invalid cmd\n");
        }
    }
}

int main(void) {
    Setup();
    return 0;
}

// unreadable code made with love
