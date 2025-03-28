#include <iostream>
#include "vm_manager.h"
#include "qemu_wrapper.h"

int main() {
    VMManager manager;

    if (!manager.connect()) {
        return 1;
    }

    std::cout << "Listing VMs..." << std::endl;
    manager.listVMs();

    std::cout << "Starting QEMU manually..." << std::endl;
    QEMUWrapper qemu("iso/archlinux-2025.03.01-x86_64.iso");
    qemu.start();

    manager.disconnect();
    return 0;
}
