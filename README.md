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

# some funny bugs
[imagem_2024-02-22_152519185](https://github.com/antiglory/simple-disasm/assets/104264903/322a170b-a7ee-423f-b4c4-5e170879007c)


# compiling
- gcc -o main main.c

! for educational porpuses/contexts only !
