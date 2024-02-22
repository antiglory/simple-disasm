#pragma once

void segfault_handler(int signal) {
    printf("\x1b[41mSEGFAULT\033[0m\n");
    exit(EXIT_FAILURE);
}