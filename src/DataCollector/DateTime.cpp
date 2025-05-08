
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "../headers/DataCollector.h"

std::string DataCollector::getDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* tm_now = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(tm_now, "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}