#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <memory>
#include "header/parsing.h"
#include "header/filesystem.h"

class BIOS {
public:
    BIOS(const std::string& isoPath) {
        isoFile.open(isoPath, std::ios::binary);
        if (!isoFile.is_open()) {
            throw std::runtime_error("Failed to open ISO file");
        }
    }

    std::vector<uint8_t> readBootSector() {
        std::vector<uint8_t> sector(512);
        isoFile.seekg(0, std::ios::beg);
        isoFile.read(reinterpret_cast<char*>(sector.data()), 512);
        if (isoFile.gcount() != 512) {
            throw std::runtime_error("Failed to read boot sector");
        }
        return sector;
    }

    bool validateMBR(const std::vector<uint8_t>& sector) {
        return (sector[510] == 0x55 && sector[511] == 0xAA);
    }

    bool validateMagicNumber() {
        std::vector<uint8_t> volumeDescriptor(2048);
        isoFile.seekg(0x8001, std::ios::beg);
        isoFile.read(reinterpret_cast<char*>(volumeDescriptor.data()), 2048);
        return (volumeDescriptor[0] == 0x43 && volumeDescriptor[1] == 0x44 &&
                volumeDescriptor[2] == 0x30 && volumeDescriptor[3] == 0x30 &&
                volumeDescriptor[4] == 0x31);
    }

    std::vector<uint8_t> readPartitionData(uint32_t startLBA, uint32_t sectorCount) {
        std::vector<uint8_t> partitionData(sectorCount * 512);
        isoFile.seekg(startLBA * 512, std::ios::beg);
        isoFile.read(reinterpret_cast<char*>(partitionData.data()), sectorCount * 512);
        return partitionData;
    }

    ~BIOS() {
        if (isoFile.is_open()) {
            isoFile.close();
        }
    }

private:
    std::ifstream isoFile;
};

class VirtualMachine {
public:
    VirtualMachine() {
        memory.resize(1024 * 1024 * 128);  // 128mb of simulated ram
    }

    void loadKernel(const std::vector<uint8_t>& kernelData) {
        std::copy(kernelData.begin(), kernelData.end(), memory.begin() + 0x10000);
    }

    void executeKernel() {
        std::cout << "Jumping to kernel at memory address 0x10000..." << std::endl;
        std::cout << "I'm over here" << std::endl;

        for (size_t i = 0; i < 64; ++i) {
            printf("%02X ", memory[0x10000 + i]);
            if ((i + 1) % 16 == 0) std::cout << std::endl;
        }
    }

private:
    std::vector<uint8_t> memory;
};

int main() {
    try {
        BIOS bios("C:/Users/swag/Desktop/Virtual Machines/Fedora-Workstation-Live-x86_64-41-1.4.iso");
        if (bios.validateMagicNumber()) {
            std::cout << "Valid ISO file detected!" << std::endl;
        } else {
            std::cout << "Invalid ISO file." << std::endl;
            return 1;
        }

        auto sector = bios.readBootSector();
        std::cout << "Boot sector loaded (512 bytes)" << std::endl;

        size_t byteLimit = 2560;
        for (size_t i = 0; i < std::min(sector.size(), byteLimit); ++i) {
            printf("%02X ", sector[i]);
            if ((i + 1) % 16 == 0) std::cout << std::endl;
            if (i >= byteLimit - 1) break;
        }

        if (bios.validateMBR(sector)) {
            std::cout << "Valid MBR signature detected!" << std::endl;

            parsePartitionTable(sector);
            std::cout << "Partition table parsed." << std::endl;

            uint32_t partitionStartLBA = 40;
            uint32_t partitionSectorCount = 1;
            std::vector<uint8_t> partitionData = bios.readPartitionData(partitionStartLBA, partitionSectorCount);
            std::cout << "Partition data read (first 512 bytes):" << std::endl;

            for (size_t i = 0; i < 512; ++i) {
                printf("%02X ", partitionData[i]);
                if ((i + 1) % 16 == 0) std::cout << std::endl;
            }

            std::unique_ptr<Filesystem> filesystem = std::make_unique<ISO9660Filesystem>(partitionData);
            std::cout << "Detecting filesystem..." << std::endl;
            filesystem->detectFilesystem();  // Check for debug output in this method
            filesystem->parse();

            std::cout << "Filesystem detection complete." << std::endl;

            VirtualMachine vm;
            vm.loadKernel(sector); 
            vm.executeKernel();

        } else {
            std::cout << "Invalid MBR signature." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
