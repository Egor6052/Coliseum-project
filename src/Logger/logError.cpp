#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "../../lib/Logger.h"

void Logger::logError(const std::string& message) {
    if (logStream.is_open()) {
        std::string timestamp = getLoggerDateTime();
        logStream << "[" << timestamp << "] ERROR: " << message << std::endl;
    }
}