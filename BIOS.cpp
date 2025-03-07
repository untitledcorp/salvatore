#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <cstdint>

class BIOS {
public:
    BIOS(const std::string& isoPath);
    ~BIOS();

    std::vector<uint8_t> readSector(size_t offset, size_t size);
    size_t findKernel();

private:
    std::ifstream isoFile;
};

BIOS::BIOS(const std::string& isoPath) {
    isoFile.open(isoPath, std::ios::binary);
    if (!isoFile.is_open()) {
        throw std::runtime_error("Failed to open ISO file.");
    }
}

BIOS::~BIOS() {
    if (isoFile.is_open()) {
        isoFile.close();
    }
}

std::vector<uint8_t> BIOS::readSector(size_t offset, size_t size) {
    isoFile.seekg(0, std::ios::end);
    size_t isoSize = isoFile.tellg();
    isoFile.seekg(offset, std::ios::beg);

    if (offset + size > isoSize) {
        std::cerr << "[Error] Trying to read beyond ISO file boundaries. Offset: " << offset << ", Size: " << size << ", ISO Size: " << isoSize << std::endl;
        throw std::runtime_error("Attempting to read beyond ISO boundaries.");
    }

    std::vector<uint8_t> sector(size);
    isoFile.read(reinterpret_cast<char*>(sector.data()), size);
    if (isoFile.gcount() != size) {
        std::cerr << "[Error] Failed to read sector. Read " << isoFile.gcount() << " bytes, expected " << size << " bytes." << std::endl;
        throw std::runtime_error("Failed to read sector.");
    }
    return sector;
}

size_t BIOS::findKernel() {
    const size_t bufferSize = 1024 * 4; 
    const std::vector<uint8_t> kernelSignature = {0x7f, 0x45, 0x4c, 0x46};

    isoFile.seekg(0, std::ios::beg);
    size_t offset = 0;
    while (isoFile) {
        std::vector<uint8_t> buffer = readSector(offset, bufferSize);

        for (size_t i = 0; i < buffer.size() - kernelSignature.size(); ++i) {
            if (std::equal(kernelSignature.begin(), kernelSignature.end(), buffer.begin() + i)) {
                std::cout << "[Info] Kernel found at offset " << std::hex << offset + i << std::dec << std::endl;
                return offset + i;  
            }
        }

        offset += bufferSize;
    }

    throw std::runtime_error("Kernel not found in the ISO.");
}
