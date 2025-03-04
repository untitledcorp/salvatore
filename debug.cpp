    #include <iostream>
    #include <fstream>
    #include <string>
    #include <ctime>
    #include <filesystem>  // To create directories if needed

    void logToFile(const std::string& logMessage) {
        // Ensure the directory exists
        if (!std::filesystem::exists("cpudmp")) {
            std::filesystem::create_directory("cpudmp");  // Create the directory if it doesn't exist
        }

        // Get current date and time
        std::time_t currentTime = std::time(nullptr);
        std::tm* tm = std::localtime(&currentTime);
        char timeBuffer[80];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm);
        
        // Open log file in append mode
        std::ofstream logFile("cpudmp/logs.txt", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << "[" << timeBuffer << "] " << logMessage << std::endl;
            logFile.close();
        } else {
            std::cerr << "Error: Could not open log file!" << std::endl;
        }
    }

    void printAndLog(const std::string& message) {
        // Print message to terminal
        std::cout << "[Debug] " << message << std::endl;
        
        // Log message to file
        logToFile(message);
    }
