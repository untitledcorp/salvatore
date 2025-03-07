#ifndef ALLOCATION_H
#define ALLOCATION_H

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <cstdint>

class Allocation {
public:
    Allocation(size_t size);
    
    ~Allocation();
    
    uint8_t* getMemory();
    
    size_t getSize() const;
    
    void write(size_t address, uint8_t value);
    
    uint8_t read(size_t address) const;
    
    void debugDump(size_t offset, size_t length) const;

private:
    uint8_t* memory;
    size_t size;
};

#endif
