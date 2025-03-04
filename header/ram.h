#pragma once

#include <cstdint> 
#include <cstddef> 

class Ram {
public:
    Ram(int sizeMB);
    ~Ram();
    uint8_t* getPointer();

private:
    uint8_t* memory;
    size_t size;
};
