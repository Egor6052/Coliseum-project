#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "../../lib/Logger.h"

Logger::Logger() {
    const std::string logFile = "../../logs/" + getLoggerDateTime() + ".log";
    logStream.open(logFile, std::ios::out | std::ios::app);
    if (!logStream) {
        std::string errorMessage = "Error: Could not open log file!";
        std::cerr << errorMessage << std::endl;
        logError(errorMessage);
    }
}

Logger::~Logger() {
    if (logStream.is_open()) {
        logStream.close();
    }
}