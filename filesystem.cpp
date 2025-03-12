#include <iostream>
#include "header/filesystem.h"

ISO9660Filesystem::ISO9660Filesystem(const std::vector<uint8_t>& partitionData) 
    : data(partitionData) {}

void ISO9660Filesystem::detectFilesystem() {
    if (data.size() > 0x8004 && data[0x8001] == 0x43 && data[0x8002] == 0x44 && data[0x8003] == 0x30 && data[0x8004] == 0x31) {
        std::cout << "ISO9660 filesystem detected!" << std::endl;
    } else {
        std::cout << "ISO9660 filesystem not detected." << std::endl;
    }
}

void ISO9660Filesystem::parse() {
    std::cout << "Parsing ISO9660 filesystem..." << std::endl;
}
FAT32Filesystem::FAT32Filesystem(const std::vector<uint8_t>& partitionData)
    : data(partitionData) {}
FAT32Filesystem::FAT32Filesystem(const std::vector<uint8_t>& partitionData) : data(partitionData) {}

void FAT32Filesystem::detectFilesystem() {
    if (data.size() > 0x37 && data[0x36] == 0x55 && data[0x37] == 0xAA) {
        std::cout << "FAT32 filesystem detected!" << std::endl;
    } else {
        std::cout << "FAT32 filesystem not detected." << std::endl;
    }
}

void FAT32Filesystem::parse() {
    std::cout << "Parsing FAT32 filesystem..." << std::endl;
}
