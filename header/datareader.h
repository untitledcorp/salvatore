#ifndef DATAREADER_H
#define DATAREADER_H

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

class DataReader {
public:
    DataReader(const std::string& isoPath);
    ~DataReader();

    std::vector<uint8_t> readPartitionData(uint32_t startLBA, uint32_t sectorCount);

private:
    std::ifstream isoFile;
};

#endif
