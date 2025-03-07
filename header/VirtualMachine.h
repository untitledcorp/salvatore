#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <cstdint>

class VirtualMachine {
public:
    VirtualMachine();  // Constructor to initialize the VM with simulated RAM
    void loadKernel(const std::vector<uint8_t>& kernelData);  // Function to load the kernel into memory
    void executeKernel();  // Function to simulate the execution of the kernel

private:
    std::vector<uint8_t> memory;  // Simulated RAM for the virtual machine
};

#endif // VIRTUALMACHINE_H
