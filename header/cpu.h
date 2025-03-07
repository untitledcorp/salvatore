#ifndef CPU_H
#define CPU_H

#include <vector>
#include <cstdint>

class ARM32Emulator {
public:
    uint32_t registers[16];
    uint32_t CPSR;
    uint32_t PC;
    std::vector<uint32_t> memory;

    ARM32Emulator(size_t memory_size);
    void loadProgram(const std::vector<uint32_t>& program);
    void execute();

private:
    void decodeAndExecute(uint32_t instruction);
    void add(uint32_t instruction);
};

#endif
