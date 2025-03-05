#include "header/parsing.h"
#include <iostream>
#include "header/datareader.h"

class PartitionTable {
public:
    PartitionTable(const std::vector<uint8_t>& mbrData) {
        for (int i = 0; i < 4; ++i) {
            Partition partition;
            size_t offset = 0x1BE + (i * 16);
            partition.status = mbrData[offset];
            partition.startCHS = readCHS(mbrData, offset + 1);
            partition.partitionType = mbrData[offset + 4];
            partition.endCHS = readCHS(mbrData, offset + 5);
            partition.startLBA = *reinterpret_cast<const uint32_t*>(&mbrData[offset + 8]);
            partition.sectorCount = *reinterpret_cast<const uint32_t*>(&mbrData[offset + 12]);

            partitions.push_back(partition);
        }
    }

    void printPartitions() {
        for (const auto& partition : partitions) {
            std::cout << "Partition Type: " << std::hex << (int)partition.partitionType
                      << " Start LBA: " << partition.startLBA
                      << " Sector Count: " << partition.sectorCount << std::endl;

            if (partition.partitionType == 0x83) {
                std::cout << "Found Linux, proceeding with filesystem detection..." << std::endl;
            }
        }
    }

private:
    struct CHS {
        uint8_t head;
        uint8_t sector;
        uint8_t cylinder;
    };

    struct Partition {
        uint8_t status;
        CHS startCHS;
        uint8_t partitionType;
        CHS endCHS;
        uint32_t startLBA;
        uint32_t sectorCount;
    };

    CHS readCHS(const std::vector<uint8_t>& data, size_t offset) {
        CHS chs;
        chs.head = data[offset];
        chs.sector = data[offset + 1];
        chs.cylinder = data[offset + 2];
        return chs;
    }

    std::vector<Partition> partitions;
};

void parsePartitionTable(const std::vector<uint8_t>& mbrData) {
    PartitionTable table(mbrData);
    table.printPartitions();
}
