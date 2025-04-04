#include <iostream>

#include "../headers/Database.h"

void Database::dataCollector(){
    std::string data = getCurrentDateTime();
    std::string ipAddress = getIpAddress();
    std::string nameSensor = getNameSensor();
    float current = roundNumber(getCurrent());
    float voltage = roundNumber(getVoltage());
    float activePower = roundNumber(getActivePower());
    float reactivePower = roundNumber(getReactivePower());

    setData(data, ipAddress, nameSensor, current, voltage, activePower, reactivePower);
}