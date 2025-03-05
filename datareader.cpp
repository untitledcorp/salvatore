#include "header/datareader.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

DataReader::DataReader(const std::string& isoPath) {
    isoFile.open(isoPath, std::ios::binary);
    if (!isoFile.is_open()) {
        throw std::runtime_error("Failed to open ISO file");
    }
}

std::vector<uint8_t> DataReader::readPartitionData(uint32_t startLBA, uint32_t sectorCount) {
    size_t totalBytes = sectorCount * 512;
    std::vector<uint8_t> buffer(totalBytes);

    isoFile.seekg(startLBA * 512, std::ios::beg);

    // ts datareader pmo he got a small ahh dih 💔✌️🥀
    // isoFile.read(reinterpret_cast<char*>(buffer.data()), totalBytes);
    // if (isoFile.gcount() != totalBytes) {
    //     throw std::runtime_error("Failed to read partition data");
    // }

    return buffer;
}

DataReader::~DataReader() {
    if (isoFile.is_open()) {
        isoFile.close();
    }
}
