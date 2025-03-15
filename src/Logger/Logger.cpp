#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "../../lib/Logger.h"

Logger::Logger() {
    const std::string logFile = "../../logs/" + getLoggerDateTime() + ".log";
    logStream.open(logFile, std::ios::out | std::ios::app);
    if (!logStream) {
        std::cerr << "Error: Could not open log file!" << std::endl;
        logError("Error: Could not open log file!");
    }
}

Logger::~Logger() {
    if (logStream.is_open()) {
        logStream.close();
    }
}