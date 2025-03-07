#ifndef BIOS_H
#define BIOS_H

#include <fstream>
#include <vector>
#include <string>
#include <cstdint>  // Include cstdint for uint8_t

class BIOS {
public:
    BIOS(const std::string& isoPath);  // Constructor to open the ISO file
    ~BIOS();  // Destructor to close the ISO file

    std::vector<uint8_t> readSector(size_t offset, size_t size);  // Function to read a sector from the ISO
    bool validatePVD();  // Function to validate the Primary Volume Descriptor

private:
    std::ifstream isoFile;  // File stream for the ISO
};

#endif // BIOS_H
