#include "header/emulation.h"
#include "header/cpu.h"
#include <iostream>
#include <vector>
#include <fstream>

void startEmulation(const std::string& isoPath, int ramMB, int cpuCores) {
    // Calculate the memory size (in bytes)
    size_t memorySize = ramMB * 1024 * 1024; // Convert MB to bytes

    // Allocate memory for the emulation
    uint8_t* memory = new uint8_t[memorySize];

    // Initialize the CPU with the allocated memory
    CPU cpu(memory);

    std::cout << "Emulation started with the following settings:\n";
    std::cout << "ISO: " << isoPath << "\n";
    std::cout << "RAM: " << ramMB << " MB\n";
    std::cout << "CPU Cores: " << cpuCores << "\n";

    // Load the ISO or initialize the system here (you can later expand this)
    std::ifstream isoFile(isoPath, std::ios::binary);
    if (isoFile.is_open()) {
        // For now, we're not loading ISO contents, but you can expand this later
        isoFile.read(reinterpret_cast<char*>(memory), memorySize);
        isoFile.close();
    } else {
        std::cerr << "Error: Failed to load ISO file.\n";
        delete[] memory;  // Don't forget to free the allocated memory!
        return;
    }

    cpu.execute(0);  // Pass an entry point (you can customize this later)

    delete[] memory;
}
