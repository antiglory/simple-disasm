# simple-disasm
a simple runtime disassembler written in C

# features
- dump instructions from .text (at process memory, not in the executable)
- explore the section with caution
- direct reading of the process
- malleable and available for modifications
- extendable opcodes interpretation (just a rubbish switch case)
- nice interface
- runtime reading

# limitations
- aimed at and only for unix-like systems
- sometimes root is needed
- easily detectable
- noisy!

# compiling
- gcc -o main main.c

! it has some bugs, but you can ignore them !

! for educational porpuses/contexts only !
