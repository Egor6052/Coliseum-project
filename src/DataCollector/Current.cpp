#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "../headers/DataCollector.h"

float DataCollector::getCurrent() {
    auto data = getDataFromPacket();
    return data["current"].get<float>();
}