# simple-disasm
a simple runtime disassembler written in C

# features
- dump instructions from .text (at process memory, not in ELF header)
- explore the segment with caution
- direct reading of the process
- malleable and available for modifications
- extendable opcodes interpretation (just a trash switch case)
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
