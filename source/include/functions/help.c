#pragma once

void printHelp() {
    printf("Usage:\n");
    printf("    ./main\n\n");
    
    printf("Set-up Commands:\n");
    printf("    set              set necessary information to run the program in the future\n");
    printf("                     including options like setting the target PID\n");
    printf("      (process_id, base_address)\n\n");
    
    printf("    get              if you need additional information if you don't have it, you can\n");
    printf("                     try using the get command to get such information, such as the base\n");
    printf("                     memory address of your target process\n");
    printf("      (base_address)\n\n");
    
    printf("    find             you can use this command to find out about some configuration that you\n");
    printf("                     previously defined using the previous commands\n");
    printf("      (process_id, base_address)\n\n");
    
    printf("    done             run this command when you are sure you have finished configuring the\n");
    printf("                     program, to load and start the interface\n\n");
    
    printf("    abort            exit command, if you need to abort or just exit the\n");
    printf("                     program, you should use this command (dont try ctrl + c)\n\n");
    
    printf("Program Commands:\n");
    printf("    dump+            dumps a defined amount of successor bytes to its current\n");
    printf("                     offset, adding it\n");
    printf("                     (example: dump+ 13 // will dump 13 bytes)\n\n");
    
    printf("    dump-            dumps a defined amount preceding its current offset, subtracting it\n");
    printf("                     (example: dump- 4 // will dump 4 bytes)\n\n");
    
    printf("    offset           prints the current offset\n\n");
    
    printf("    find             prints information based\n");
    printf("                     (example: find buffer limit)\n");
    printf("       (buffer;\n");
    printf("          limit)\n\n");
    
    printf("    goto             replaces the current offset with the desired offset\n");
    printf("                     (example: goto 1024 // will go to byte 1024)\n\n");
    
    printf("    clear            clears printed information\n\n");

    printf("Notes:\n");

    printf("    : | main program prompt\n");
    printf("    + | setup prompt\n\n");
}