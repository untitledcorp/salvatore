#include <iostream>
#include "header/BIOS.h"
#include "header/VirtualMachine.h"
#include "header/bootloader.h"
#include "header/filesystem.h"
#include "header/allocation.h"
#include "header/cpu.h"
#include "header/vgadriver.h"

const std::string kIsoPath = "iso/archlinux-2025.03.01-x86_64.iso";

int main() {
    try {
        vga_clear_screen();

        vga_print("Starting virtual machine...\n");

        size_t ramSize = 1024 * 1024 * 1024; // 1GB of RAM (1024 * 1024 * 1024 bytes)
 
        Allocation ram(ramSize);

        std::string ramMessage = "Allocated " + std::to_string(ram.getSize() / (1024 * 1024)) + " MB of RAM.";
        vga_print(ramMessage.c_str());
        vga_print("\n");

        std::string isoPath = kIsoPath;
        
        Bootloader bootloader(isoPath);
        
        auto bootSector = bootloader.readBootSector();
        vga_print("Boot sector loaded.\n");

        if (!bootloader.validateMBR(bootSector)) {
            vga_print("Invalid MBR or boot sector.\n");
            return 1;
        }
        
        size_t kernelOffset = 0x1000;
        size_t kernelSize = 1024 * 1024;
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
        vga_print("Error: ");
        vga_print(e.what());
        vga_print("\n");
        return 1;
    }

    return 0;
}
