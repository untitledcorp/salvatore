#ifndef QEMU_WRAPPER_H
#define QEMU_WRAPPER_H

#include <string>

class QEMUWrapper {
public:
    QEMUWrapper(const std::string &isoPath);
    void start();
private:
    std::string isoPath;
};

#endif
