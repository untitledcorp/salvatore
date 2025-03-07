#include <iostream>
#include "header/BIOS.h"
#include "header/VirtualMachine.h"
#include "header/bootloader.h"
#include "header/filesystem.h"
#include "header/allocation.h"
#include "header/cpu.h"

const std::string kIsoPath = "iso/archlinux-2025.03.01-x86_64.iso";

int main() {
    try {
        size_t ramSize = 1024 * 1024 * 1024; // 1GB of RAM (1024 * 1024 * 1024 bytes)

        Allocation ram(ramSize);

        std::cout << "Allocated " << ram.getSize() / (1024 * 1024) << " MB of RAM." << std::endl;
        
        std::string isoPath = kIsoPath;
        
        Bootloader bootloader(isoPath);
        
        auto bootSector = bootloader.readBootSector();
        std::cout << "Boot sector loaded." << std::endl;

        if (!bootloader.validateMBR(bootSector)) {
            std::cerr << "Invalid MBR or boot sector." << std::endl;
            return 1;
        }
        
        size_t kernelOffset = 0x1000; // Offset for kernel loading
        size_t kernelSize = 1024 * 1024; // Size of the kernel
        bootloader.loadKernel(kernelOffset, kernelSize);

        bootloader.jumpToKernel();

        ARM32Emulator cpu(1024);

        // Sample ARM32 instructions
        std::vector<uint32_t> program = {
            0xE0800002,
            0xE0801003
        };

        cpu.loadProgram(program);
        cpu.execute();

        ISO9660Filesystem isoFilesystem(bootSector);
        isoFilesystem.detectFilesystem();
        isoFilesystem.parse();

        FAT32Filesystem fat32Filesystem(bootSector);
        fat32Filesystem.detectFilesystem();
        fat32Filesystem.parse();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
