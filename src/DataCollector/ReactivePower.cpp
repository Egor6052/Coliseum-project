#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>
#include "../headers/DataCollector.h"

float DataCollector::getReactivePower() {
    auto data = getDataFromPacket();
    return data["reactivePower"].get<float>();
}