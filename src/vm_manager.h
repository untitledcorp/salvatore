#ifndef VM_MANAGER_H
#define VM_MANAGER_H

#include "../include/libvirt/libvirt.h"
#include <string>

class VMManager {
public:
    VMManager();
    ~VMManager();

    bool connect();
    void disconnect();
    bool createVM(const std::string &xmlConfig);
    void listVMs();
    bool startVM(const std::string &vmName);
    bool stopVM(const std::string &vmName);
private:
    virConnectPtr conn;
};

#endif
