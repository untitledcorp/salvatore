#include "header/cpu.h"
#include <iostream>
#include <cstdint>  // Add this line for uint8_t
#include <cstddef>  // Add this line for size_t

// he thought C++ was easy as shit, he mad as hell 😭😂✌️💔
CPU::CPU(uint8_t* mem) : memory(mem), AX(0), BX(0), CX(0), DX(0), IP(0x7C00) {}

void CPU::execute(uint32_t entryPoint) {
    IP = entryPoint;
    uint32_t offset = 0;  // Move the declaration here
    
    while (true) {
        uint8_t opcode = memory[IP++];
        
        switch (opcode) {
        case 0xB8:
            AX = memory[IP++] | (memory[IP++] << 8);
            break;

        case 0xE9:
            offset = memory[IP++] | (memory[IP++] << 8) | (memory[IP++] << 16) | (memory[IP++] << 24);
            IP += offset;
            break;

        case 0xF4:
            std::cout << "[Salvatore] Halted CPU execution.\n";
            return;

        default:
            std::cout << "[Salvatore] Unknown opcode: " << std::hex << (int)opcode << std::dec << "\n";
            hlt();
            break;
        }
    }
}


void CPU::hlt() {
    std::cout << "[Salvatore] HALT! Stopping execution.\n";
    exit(0);  // Stop program (can replace with better error handling later)
}
