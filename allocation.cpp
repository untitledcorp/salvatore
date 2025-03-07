#include "header/allocation.h"
#include <iostream>
#include <cstring>

Allocation::Allocation(size_t size) : size(size) {
    memory = new uint8_t[size];
    if (!memory) {
        throw std::runtime_error("Failed to allocate memory");
    }
    std::memset(memory, 0, size);
    std::cout << "[RAM] Allocated " << size / (1024 * 1024) << " MB of memory" << std::endl;
}

Allocation::~Allocation() {
    delete[] memory;
    std::cout << "[RAM] Memory freed" << std::endl;
}

uint8_t* Allocation::getMemory() {
    return memory;
}

size_t Allocation::getSize() const {
    return size;
}

void Allocation::write(size_t address, uint8_t value) {
    if (address >= size) {
        throw std::out_of_range("Memory write out of range");
    }
    memory[address] = value;
}

uint8_t Allocation::read(size_t address) const {
    if (address >= size) {
        throw std::out_of_range("Memory read out of range");
    }
    return memory[address];
}

void Allocation::debugDump(size_t offset, size_t length) const {
    std::cout << "[RAM] Memory Dump at offset " << std::hex << offset << " for " << std::dec << length << " bytes" << std::endl;
    for (size_t i = 0; i < length; ++i) {
        if (i % 16 == 0) std::cout << std::endl;
        std::cout << std::hex << static_cast<int>(memory[offset + i]) << " ";
    }
    std::cout << std::dec << std::endl;
}