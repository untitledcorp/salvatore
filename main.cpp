#include <cstdlib>  // For system()
#include <iostream>
#include <string>
#include <filesystem>
#include "header/isohandler.h"
#include "header/ram.h"
#include "header/cpu.h"
#include "header/debug.h"  // Include the debug header

void openDebugWindow() {
    std::cout << "[Salvatore] Opening debug window...\n";
    system("start powershell -Command \"Get-Content cpudmp/logs.txt -Wait\"");  // For Windows
}

int main() {
    std::string isoPath;
    int ramMB;
    int cpuCores;

    std::cout << R"(salvatore.
(C) zekkie, 2025, MIT license.
    )" << "\n\n";

    // Open the debug window right away
    openDebugWindow();  // This will open the debug window at the start

    std::cout << "Drag and drop the .iso file here and press Enter: ";
    std::getline(std::cin, isoPath);

    if (isoPath.front() == '"' && isoPath.back() == '"') {
        isoPath = isoPath.substr(1, isoPath.length() - 2);
    }

    // Log the file path
    printAndLog("ISO Path: " + isoPath);

    if (!std::filesystem::exists(isoPath)) {
        std::cerr << "Error: File not found.\n";
        printAndLog("Error: ISO file not found.");
        return 1;
    }

    IsoHandler iso(isoPath);
    if (!iso.isValidIso()) {
        std::cerr << "Error: Invalid ISO file.\n";
        printAndLog("Error: Invalid ISO file.");
        return 1;
    }

    printAndLog("ISO validated successfully.");

    std::cout << "Enter RAM allocation (in MB): ";
    std::cin >> ramMB;
    if (ramMB <= 0) {
        std::cerr << "Error: RAM must be greater than 0.\n";
        printAndLog("Error: RAM allocation invalid.");
        return 1;
    }

    printAndLog("RAM allocation: " + std::to_string(ramMB) + " MB.");

    std::cout << "Enter the number of CPU cores to use: ";
    std::cin >> cpuCores;
    if (cpuCores <= 0) {
        std::cerr << "Error: CPU cores must be greater than 0.\n";
        printAndLog("Error: CPU cores invalid.");
        return 1;
    }

    printAndLog("CPU cores selected: " + std::to_string(cpuCores));

    Ram ram(ramMB);
    uint8_t* ramPtr = ram.getPointer();

    if (!ramPtr) {
        std::cerr << "Error: RAM allocation failed.\n";
        printAndLog("Error: RAM allocation failed.");
        return 1;
    }

    printAndLog("RAM pointer allocated at: " + std::to_string(reinterpret_cast<uintptr_t>(ramPtr)));

    std::string bootSector = iso.getBootSector();
    if (bootSector.empty()) {
        std::cerr << "Error: No boot sector found.\n";
        printAndLog("Error: No boot sector found.");
        return 1;
    }

    printAndLog("Boot sector found. Loading to memory.");

    memcpy(ramPtr + 0x7C00, bootSector.c_str(), bootSector.size());  // Load boot sector into memory

    CPU cpu(ramPtr);
    printAndLog("Starting CPU execution...");
    cpu.execute(0x7C00);  // Start execution from the bootloader

    std::cout << "Press Enter to exit...\n";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
