#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <fstream>
#include <vector>
#include <cstdint>

class Bootloader {
public:
    Bootloader(const std::string& isoPath);
    ~Bootloader();

    std::vector<uint8_t> readBootSector();
    bool validateMBR(const std::vector<uint8_t>& sector);
    void loadKernel();
    void jumpToKernel();
    void loadKernel(size_t kernelOffset, size_t kernelSize);

private:
    void kernelEntry();

    std::ifstream isoFile;
    std::vector<uint8_t> kernelData;
};

#endif
