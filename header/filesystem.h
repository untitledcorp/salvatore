#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <vector>
#include <string>
#include <cstdint>

class Filesystem {
public:
    virtual void detectFilesystem() = 0;
    virtual void parse() = 0;
};

class ISO9660Filesystem : public Filesystem {
public:
    ISO9660Filesystem(const std::vector<uint8_t>& partitionData);
    void detectFilesystem() override;
    void parse() override;
private:
    const std::vector<uint8_t>& data;
};

class FAT32Filesystem : public Filesystem {
public:
    FAT32Filesystem(const std::vector<uint8_t>& partitionData);
    void detectFilesystem() override;
    void parse() override;
private:
    const std::vector<uint8_t>& data;
};

#endif
