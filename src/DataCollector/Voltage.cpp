#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>
#include "../headers/DataCollector.h"

float DataCollector::getVoltage() {
    auto data = getDataFromPacket();
    return data["voltage"].get<float>();
}