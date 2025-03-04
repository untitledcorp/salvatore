#include "header\ram.h"
#include <iostream>
#include <cstdint>  // Add this line for uint8_t
#include <cstddef>  // Add this line for size_t

Ram::Ram(int sizeMB) {
    size = sizeMB * 1024 * 1024;
    memory = new uint8_t[size];
    std::fill(memory, memory + size, 0);
    std::cout << "Allocated " << sizeMB << "MB RAM\n";
}

Ram::~Ram() {
    delete[] memory;
    std::cout << "Freed RAM\n";
}

uint8_t* Ram::getPointer() {
    return memory;
}
