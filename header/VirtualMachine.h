#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <cstdint>

class VirtualMachine {
public:
    VirtualMachine();
    void loadKernel(const std::vector<uint8_t>& kernelData);
    void executeKernel();

private:
    std::vector<uint8_t> memory;
};

#endif 