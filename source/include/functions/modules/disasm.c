// disasm.c

#pragma once

void disasm(uint8_t *buffer, int offset) {
    uint8_t opcode = buffer[offset];
    
    switch (opcode) {
        // ADD instruction
        case 0x01:
            printf("ADD AL, %02X\n", buffer[offset + 1]);
            break;
        // MOV instruction
        case 0x89:
            printf("MOV CX, [BX+DI] ; 0x%01x\n", &buffer[offset]);
            break;
        // JMP instruction
        case 0xEB:
            printf("JMP SHORT %02X\n", buffer[offset + 1]);
            break;
        // NOP instruction
        case 0x90:
            printf("NOP\n");
            break;
        // CALL instruction
        case 0xE8:
            printf("CALL NEAR %02X%02X%02X%02X\n", buffer[offset + 3], buffer[offset + 2], buffer[offset + 1], buffer[offset]);
            break;
        // PUSH instruction
        case 0x50:
            printf("PUSH AX\n");
            break;
        // POP instruction
        case 0x58:
            printf("POP AX\n");
            break;
        // XOR instruction
        case 0x33:
            printf("XOR AX, BX\n");
            break;
        // INC instruction
        case 0xFE:
            printf("INC [DI]\n");
            break;
        // DEC instruction
        case 0xFF:
            printf("DEC [SI]\n");
            break;
        // SUB instruction
        case 0x29:
            printf("SUB CX, DX\n");
            break;
        // MOVSB instruction
        case 0xA4:
            printf("MOVSB\n");
            break;
        // CMP instruction
        case 0x3B:
            printf("CMP AX, BX\n");
            break;
        // JE instruction
        case 0x74:
            printf("JE SHORT %02X\n", buffer[offset + 1]);
            break;
        // JNE instruction
        case 0x75:
            printf("JNE SHORT %02X\n", buffer[offset + 1]);
            break;
        // AND instruction
        case 0x21:
            printf("AND AX, BX\n");
            break;
        // OR instruction
        case 0x09:
            printf("OR CX, DX\n");
            break;
        // SHL instruction
        case 0xD3:
            printf("SHL AX, 1\n");
            break;
        // SHR instruction
        case 0xD1:
            printf("SHR CX, 1\n");
            break;
        // RET instruction
            case 0xC3:
            printf("RET\n");
            break;
        // MUL instruction
        case 0xF7:
            printf("MUL BX\n");
            break;
        // DIV instruction
        case 0xF6:
            printf("DIV CX\n");
            break;
        // LEA instruction
        case 0x8D:
            printf("LEA DX, [SI]\n");
            break;
        // XCHG instruction
        case 0x87:
            printf("XCHG AX, CX\n");
            break;
        // LOOP instruction
        case 0xE2:
            printf("LOOP SHORT %02X\n", buffer[offset + 1]);
            break;
        // REP instruction
        case 0xF3:
            printf("REP\n");
            break;
        // CLC instruction
        case 0xF8:
            printf("CLC\n");
            break;
        // STC instruction
        case 0xF9:
            printf("STC\n");
            break;
        // CLI instruction
        case 0xFA:
            printf("CLI\n");
            break;
        // STI instruction
        case 0xFB:
            printf("STI\n");
            break;
        // CWD instruction
        case 0x99:
            printf("CWD\n");
            break;
        // INT instruction
        case 0xCD:
            printf("INT %02X\n", buffer[offset + 1]);
            break;
        // IRET instruction
        case 0xCF:
            printf("IRET\n");
            break;
        // HLT instruction
        case 0xF4:
            printf("HLT\n");
            break;
        // ROL instruction
        case 0xD0:
            printf("ROL CX, 1\n");
            break;
        // ROR instruction
        case 0xD8:
            printf("ROR DX, 1\n");
            break;
        // SAR instruction
        case 0xC1:
            printf("SAR BX, 1\n");
            break;
        // TEST instruction
        case 0x85:
            printf("TEST CX, DX\n");
            break;
        // if unknow instruction
        default:
            printf("NULL\n");
            break;
    }
}