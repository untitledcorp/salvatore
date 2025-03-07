#include <iostream>
#include <vector>
#include <stdexcept>
#include "header/cpu.h"

ARM32Emulator::ARM32Emulator(size_t memory_size) : memory(memory_size, 0), PC(0) {
    std::fill(std::begin(registers), std::end(registers), 0);
    CPSR = 0;
}

void ARM32Emulator::loadProgram(const std::vector<uint32_t>& program) {
    if (program.size() > memory.size()) {
        throw std::overflow_error("Program is too large to fit into memory");
    }
    std::copy(program.begin(), program.end(), memory.begin());
}

void ARM32Emulator::execute() {
    while (PC < memory.size()) {
        uint32_t instruction = memory[PC / 4];
        decodeAndExecute(instruction);
        PC += 4;
    }
}

void ARM32Emulator::decodeAndExecute(uint32_t instruction) {
    uint8_t opcode = (instruction >> 21) & 0xF;
    switch (opcode) {
        case 0x0:
            add(instruction);
            break;

        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
            break;
    }
}

void ARM32Emulator::add(uint32_t instruction) {
    uint8_t rd = (instruction >> 12) & 0xF;
    uint8_t rn = (instruction >> 16) & 0xF;
    uint8_t rm = instruction & 0xF;

    registers[rd] = registers[rn] + registers[rm];
    std::cout << "ADD: R" << (int)rd << " = R" << (int)rn << " + R" << (int)rm << std::endl;
}
