#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include <limits.h>
#include <filesystem>

#include "../headers/Logger.h"

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

Logger::Logger() {

    std::string logFile = absolutePath() + "../logs/" + getLoggerDateTime() + ".log";

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

std::string Logger::absolutePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        auto path = std::filesystem::path(std::string(result, count));
        return path.parent_path().parent_path().string();
    } else {
        return "";
    }
}