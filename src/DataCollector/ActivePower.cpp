#include <iostream>
#include <string.h>
#include <cmath>
#include "../headers/DataCollector.h"

float DataCollector::getActivePower() {
    auto data = getDataFromPacket();
    return data["activePower"].get<float>();
}