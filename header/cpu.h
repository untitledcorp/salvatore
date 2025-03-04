#pragma once
#include <cstdint>

class CPU {
public:
    CPU(uint8_t* memory);
    void execute(uint32_t entryPoint);

private:
    // Registers
    uint16_t AX, BX, CX, DX, IP;

    // Memory pointer
    uint8_t* memory;

    // Instruction set
    void mov(uint16_t& reg, uint16_t value);
    void jmp(uint32_t address);
    void hlt();
};
