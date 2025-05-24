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
    std::string logDir = absolutePath() + "../logs/";
    namespace fs = std::filesystem;

    // Ensure log directory exists
    try {
        if (!fs::exists(logDir)) {
            fs::create_directories(logDir);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error creating log directory: " << e.what() << std::endl;
        return;
    }

    // Get current date (YYYY-MM-DD)
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream dateStream;
    dateStream << std::put_time(std::localtime(&time), "%Y-%m-%d");
    std::string currentDate = dateStream.str(); // e.g., "2025-05-21"

    // Auto-delete log files older than 30 days
    try {
        if (fs::exists(logDir)) {
            for (const auto& entry : fs::directory_iterator(logDir)) {
                if (entry.is_regular_file()) {
                    auto ftime = fs::last_write_time(entry);
                    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                        ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
                    );
                    auto age = std::chrono::duration_cast<std::chrono::hours>(now - sctp).count();
                    if (age > 24 * 30) {
                        fs::remove(entry);
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Log cleanup error: " << e.what() << std::endl;
    }

    // Search for log file with current date
    std::string logFile;
    bool fileFound = false;
    try {
        for (const auto& entry : fs::directory_iterator(logDir)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.find(currentDate) != std::string::npos &&
                    filename.size() >= 4 && filename.compare(filename.size() - 4, 4, ".log") == 0) {
                    logFile = entry.path().string();
                    fileFound = true;
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error scanning log directory: " << e.what() << std::endl;
    }

    // Open existing file or create new one
    if (fileFound) {
        logStream.open(logFile, std::ios::out | std::ios::app);
        if (logStream) {
            logStream << "\nAppending to log file on " << getLoggerDateTime() << "\n";
            logStream << "----------------------------------------\n";
        }
    } else {
        logFile = logDir + currentDate + ".log";
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