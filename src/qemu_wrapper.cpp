#include "qemu_wrapper.h"
#include <iostream>
#include <cstdlib>

QEMUWrapper::QEMUWrapper(const std::string &isoPath) : isoPath(isoPath) {}

void QEMUWrapper::start() {
    std::string cmd = "qemu-system-x86_64 -m 2G -cdrom " + isoPath + " -boot d";
    std::cout << "Starting QEMU with command: " << cmd << std::endl;
    std::system(cmd.c_str());
}