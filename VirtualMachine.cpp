#include "header/VirtualMachine.h"
#include <iostream>
#include <vector>

VirtualMachine::VirtualMachine() {
    memory.resize(1024 * 1024 * 128);  // 128MB simulated RAM
}

void VirtualMachine::loadKernel(const std::vector<uint8_t>& kernelData) {
    std::copy(kernelData.begin(), kernelData.end(), memory.begin() + 0x10000);
    std::cout << "Kernel loaded into memory at 0x10000." << std::endl;
}

void VirtualMachine::executeKernel() {
    std::cout << "Simulating kernel execution..." << std::endl;
    for (size_t i = 0; i < 64; ++i) {
        printf("%02X ", memory[0x10000 + i]);
        if ((i + 1) % 16 == 0) std::cout << std::endl;
    }
}
