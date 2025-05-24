#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>

#include "../headers/DataCollector.h"

DataCollector::DataCollector() { dataCollector(); }

DataCollector::~DataCollector() {   }

std::string DataCollector::dataCollector() {
    // Формування об'єкта JSON
    nlohmann::json jsonData = {
        {"data", getDateTime()},
        {"ipAddress", getIpAddress()},
        {"nameSensor", getNameSensor()},
        {"current", roundNumber(getCurrent())},
        {"voltage", roundNumber(getVoltage())},
        {"activePower", roundNumber(getActivePower())},
        {"reactivePower", roundNumber(getReactivePower())}
    };

    std::cout << "Data: " << jsonData.dump() << std::endl;
    return jsonData.dump();
}
