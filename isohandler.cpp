#include "header\isohandler.h"
#include <fstream>
#include <iostream>
#include <cstdint>  // Add this for uint32_t

IsoHandler::IsoHandler(const std::string& path) : isoPath(path) {}

bool IsoHandler::isValidIso() {
    std::ifstream isoFile(isoPath, std::ios::binary);
    if (!isoFile) {
        std::cerr << "Error: Cannot open ISO file.\n";
        return false;
    }

    // Check if the file is large enough to be a valid ISO (minimum size for ISO 9660)
    isoFile.seekg(0, std::ios::end);
    size_t fileSize = isoFile.tellg();
    if (fileSize < 2048) {  // Minimum size for a valid ISO
        std::cerr << "Error: File is too small to be a valid ISO.\n";
        return false;
    }

    std::cout << "[Salvatore] ISO file size: " << fileSize << " bytes\n";

    // Read the first 32 bytes to check the start of the ISO
    isoFile.seekg(0);
    char buffer[32];
    isoFile.read(buffer, 32);
    std::cout << "[Salvatore] First 32 bytes of ISO: ";
    for (int i = 0; i < 32; ++i) {
        std::cout << std::hex << (int)(unsigned char)buffer[i] << " ";
    }
    std::cout << std::dec << std::endl;

    // Magic number check at 32769 (0x8001) for ISO 9660 standard
    isoFile.seekg(0x8001);
    char magic[5] = {};
    isoFile.read(magic, 5);
    std::cout << "[Salvatore] Magic number at 0x8001: " << magic << std::endl;

    if (std::string(magic) != "CD001") {
        std::cerr << "[Salvatore] Invalid ISO: Magic number mismatch.\n";
        return false;
    }

    // Check for Boot Catalog in El Torito (check at 0x8000 + 0x47 for boot catalog location)
    isoFile.seekg(0x8000 + 0x47);
    uint32_t bootCatalogOffset = 0;
    isoFile.read(reinterpret_cast<char*>(&bootCatalogOffset), 4);
    std::cout << "[Salvatore] Boot Catalog Offset: " << bootCatalogOffset << std::endl;

    if (bootCatalogOffset == 0) {
        std::cerr << "[Salvatore] No bootable sector found (El Torito missing).\n";
        return false;
    }

    std::cout << "[Salvatore] Valid ISO found and bootable sector located.\n";
    return true;
}




std::string IsoHandler::getBootSector() {
    std::ifstream isoFile(isoPath, std::ios::binary);
    if (!isoFile) {
        std::cerr << "Error: Cannot open ISO file.\n";
        return "";
    }

    // El Torito Boot Catalog location at 0x47 in Primary Volume Descriptor
    isoFile.seekg(0x8000 + 0x47);
    uint32_t bootCatalogOffset = 0;
    isoFile.read(reinterpret_cast<char*>(&bootCatalogOffset), 4);

    if (bootCatalogOffset == 0) {
        std::cerr << "[Salvatore] No boot sector found.\n";
        return "";
    }

    std::cout << "[Salvatore] Boot Catalog found at sector: " << bootCatalogOffset << "\n";

    // Read boot sector bytes
    isoFile.seekg(bootCatalogOffset * 2048);
    char bootSector[512] = {};
    isoFile.read(bootSector, 512);

    return std::string(bootSector, 512);
}
