#include <iostream>
#include <string>
#include <filesystem>
#include "header\isohandler.h"

int main() {
    std::string isoPath;
    int ramMB;
    int cpuCores;

    std::cout << R"(
               .__                __                        
  ___________  |  |___  _______ _/  |_  ___________   ____  
 /  ___/\__  \ |  |\  \/ /\__  \\   __\/  _ \_  __ \_/ __ \ 
 \___ \  / __ \|  |_\   /  / __ \|  | (  <_> )  | \/\  ___/ 
/____  >(____  /____/\_/  (____  /__|  \____/|__|    \___  >
     \/      \/                \/                        \/
(C) zekkie, 2025, MIT license
    )" << "\n\n";

    std::cout << "Drag and drop the .iso file here and press Enter: ";
    std::getline(std::cin, isoPath);

    if (isoPath.front() == '"' && isoPath.back() == '"') {
        isoPath = isoPath.substr(1, isoPath.length() - 2);
    }

    if (!std::filesystem::exists(isoPath)) {
        std::cerr << "Error: File not found.\n";
        return 1;
    }

    std::cout << "Enter RAM allocation (in MB): ";
    std::cin >> ramMB;

    if (ramMB <= 0) {
        std::cerr << "Error: RAM must be greater than 0.\n";
        return 1;
    }

    std::cout << "Enter the number of CPU cores to use: ";
    std::cin >> cpuCores;

    if (cpuCores <= 0) {
        std::cerr << "Error: CPU cores must be greater than 0.\n";
        return 1;
    }

    std::cout << "\nStarting Salvatore with the following settings:\n";
    std::cout << "ISO: " << isoPath << "\n";
    std::cout << "RAM: " << ramMB << " MB\n";
    std::cout << "CPU Cores: " << cpuCores << "\n";
    std::cout << "Booting...\n";

    std::cout << "Press Enter to exit the program...\n";
    std::cin.ignore(); 
    std::cin.get();

    return 0;
}
