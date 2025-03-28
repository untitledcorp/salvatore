#include "vm_manager.h"
#include <iostream>

VMManager::VMManager() : conn(nullptr) {}

VMManager::~VMManager() {
    disconnect();
}

bool VMManager::connect() {
    conn = virConnectOpen("qemu:///session");
    if (!conn) {
        std::cerr << "Failed to connect to libvirt" << std::endl;
        return false;
    }
    return true;
}

void VMManager::disconnect() {
    if (conn) {
        virConnectClose(conn);
        conn = nullptr;
    }
}

bool VMManager::createVM(const std::string &xmlConfig) {
    if (!conn) return false;
    virDomainPtr dom = virDomainCreateXML(conn, xmlConfig.c_str(), 0);
    if (!dom) {
        std::cerr << "Failed to create VM" << std::endl;
        return false;
    }
    virDomainFree(dom);
    return true;
}

void VMManager::listVMs() {
    if (!conn) return;
    int numDomains = virConnectNumOfDomains(conn);
    if (numDomains < 0) return;

    int *activeDomains = new int[numDomains];
    virConnectListDomains(conn, activeDomains, numDomains);

    std::cout << "Active VMs:" << std::endl;
    for (int i = 0; i < numDomains; i++) {
        virDomainPtr dom = virDomainLookupByID(conn, activeDomains[i]);
        if (dom) {
            std::cout << " - " << virDomainGetName(dom) << std::endl;
            virDomainFree(dom);
        }
    }
    delete[] activeDomains;
}

bool VMManager::startVM(const std::string &vmName) {
    if (!conn) return false;
    virDomainPtr dom = virDomainLookupByName(conn, vmName.c_str());
    if (!dom) return false;
    return virDomainCreate(dom) == 0;
}

bool VMManager::stopVM(const std::string &vmName) {
    if (!conn) return false;
    virDomainPtr dom = virDomainLookupByName(conn, vmName.c_str());
    if (!dom) return false;
    return virDomainShutdown(dom) == 0;
}
