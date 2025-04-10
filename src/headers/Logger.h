#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
private:
    std::ofstream logStream;
    std::string absolutePath();


public:
    Logger();
    ~Logger();

    std::string getLoggerDateTime();
    
    void logError(const std::string& message);
};