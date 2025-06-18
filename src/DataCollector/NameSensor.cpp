#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>
#include "../headers/DataCollector.h"

std::string DataCollector::getNameSensor() {
    auto data = getDataFromPacket();
    return data["sensorName"].get<std::string>();
}
