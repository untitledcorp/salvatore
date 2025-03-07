#include <iostream>
#include "header/BIOS.h"
#include "header/VirtualMachine.h"
#include "header/bootloader.h"
#include "header/filesystem.h"
#include "header/allocation.h"

int main() {
    try {
        size_t ramSize = 4 * 1024 * 1024; // 4mb

        Allocation ram(ramSize);

        std::cout << "Allocated " << ram.getSize() / (1024 * 1024) << " MB of RAM." << std::endl;
        
        std::string isoPath = "iso/archlinux-2025.03.01-x86_64.iso";
        
        Bootloader bootloader(isoPath);
        
        auto bootSector = bootloader.readBootSector();
        std::cout << "Boot sector loaded." << std::endl;

        if (!bootloader.validateMBR(bootSector)) {
            std::cerr << "Invalid MBR or boot sector." << std::endl;
            return 1;
        }
        
        size_t kernelOffset = 0x1000;
        size_t kernelSize = 1024 * 1024;
        bootloader.loadKernel(kernelOffset, kernelSize);

        bootloader.jumpToKernel();

        VirtualMachine vm;
        vm.loadKernel(bootSector);
        vm.executeKernel();

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
