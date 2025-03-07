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

    kernelData.resize(kernelSize);
    isoFile.seekg(kernelOffset, std::ios::beg);
    isoFile.read(reinterpret_cast<char*>(kernelData.data()), kernelSize);

    if (isoFile.gcount() != kernelSize) {
        throw std::runtime_error("Failed to read kernel data");
    }
    std::cout << "[Bootloader] Kernel loaded successfully into memory" << std::endl;
}

void Bootloader::jumpToKernel() {
    std::cout << "[Bootloader] Heading to kernel..." << std::endl;

    if (kernelData.empty()) {
        throw std::runtime_error("Kernel data is empty — cannot jump to kernel.");
    }

    kernelEntry();
}

void Bootloader::kernelEntry() {
    std::cout << "[Kernel] haiiiii :333 >_<" << std::endl;
    std::cout << "[Kernel] Executing kernel payload..." << std::endl;

    std::cout << "[Kernel] First 16 bytes of kernel: ";
    for (int i = 0; i < 16 && i < kernelData.size(); ++i) {
        std::cout << std::hex << (int)kernelData[i] << " ";
    }
    std::cout << std::dec << std::endl;
}
