#include <iostream>
#include <string.h>
#include <random>
#include "../headers/DataCollector.h"

std::string DataCollector::getIpAddress() {
    auto data = getDataFromPacket();
    return data["ipAddress"].get<std::string>();
}