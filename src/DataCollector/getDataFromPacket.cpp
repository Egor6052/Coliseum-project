#include <iostream>
#include <string.h>
#include <cmath>
#include "../headers/DataCollector.h"

json DataCollector::getDataFromPacket() {
    std::string packetStr = RS485();
    return json::parse(packetStr);
}