#include "header/bootloader.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

Bootloader::Bootloader(const std::string& isoPath) {
    isoFile.open(isoPath, std::ios::binary);
    if (!isoFile.is_open()) {
        throw std::runtime_error("Failed to open ISO file");
    }
}

Bootloader::~Bootloader() {
    if (isoFile.is_open()) {
        isoFile.close();
    }
}

std::vector<uint8_t> Bootloader::readBootSector() {
    std::vector<uint8_t> sector(512);
    isoFile.seekg(0, std::ios::beg);
    isoFile.read(reinterpret_cast<char*>(sector.data()), 512);
    if (isoFile.gcount() != 512) {
        throw std::runtime_error("Failed to read boot sector");
    }
    return sector;
}

bool Bootloader::validateMBR(const std::vector<uint8_t>& sector) {
    return (sector[510] == 0x55 && sector[511] == 0xAA);
}

void Bootloader::loadKernel(size_t kernelOffset, size_t kernelSize) {
    std::cout << "Loading kernel from offset " << kernelOffset << " with size " << kernelSize << "..." << std::endl;
    isoFile.seekg(kernelOffset, std::ios::beg);
    isoFile.read(reinterpret_cast<char*>(kernelData.data()), kernelSize);
    if (isoFile.gcount() != kernelSize) {
        throw std::runtime_error("Failed to read kernel data");
    }
}


void Bootloader::jumpToKernel() {
    std::cout << "Jumping to kernel..." << std::endl;
    kernelEntry();
}

void Bootloader::kernelEntry() {
    std::cout << "Kernel started!" << std::endl;
    std::cout << "Kernel is now running..." << std::endl;
}
