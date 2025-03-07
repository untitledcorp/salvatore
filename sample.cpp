#include <iostream>
#include "header/cpu.h"

void testCpuEmulation() {
    ARM32Emulator cpu(1024);

    std::vector<uint32_t> program = {
        0xE0800002,
        0xE0801003,
    };

    cpu.loadProgram(program);
    cpu.execute();
}

int mainSample() {
    testCpuEmulation();
    return 0;
}
