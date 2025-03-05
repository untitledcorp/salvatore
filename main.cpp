#include <iostream>
#include <fstream>
#include <vector>

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

    ~BIOS() {
        if (isoFile.is_open()) {
            isoFile.close();
        }
    }

private:
    std::ifstream isoFile;
};

int main() {
    try {
        BIOS bios("archlinux.iso");
        auto sector = bios.readBootSector();
        std::cout << "Boot sector loaded (512 bytes)" << std::endl;
        for (size_t i = 0; i < sector.size(); ++i) {
            printf("%02X ", sector[i]);
            if ((i + 1) % 16 == 0) std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}