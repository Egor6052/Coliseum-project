#include "../headers/Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string Logger::getLoggerDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* tm_now = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(tm_now, "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}