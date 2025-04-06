#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "../headers/Logger.h"

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

Logger::Logger() {
    std::string logFile = "../logs/" + getLoggerDateTime() + ".log";

    if (fileExists(logFile)) {
        logStream.open(logFile, std::ios::out | std::ios::app);
    } else {
        logStream.open(logFile, std::ios::out);
        if (logStream) {
            logStream << "Log file created on " << getLoggerDateTime() << "\n";
            logStream << "----------------------------------------\n";
        }
    }

    if (!logStream) {
        std::string errorMessage = "Error: Could not open log file " + logFile + "!";
        std::cerr << errorMessage << std::endl;
        logError(errorMessage);
    }
}

Logger::~Logger() {
    if (logStream.is_open()) {
        logStream.close();
    }
}