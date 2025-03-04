#pragma once
#include <string>

class IsoHandler {
public:
    IsoHandler(const std::string& path);
    bool isValidIso();
    std::string getBootSector();

private:
    std::string isoPath;
};
