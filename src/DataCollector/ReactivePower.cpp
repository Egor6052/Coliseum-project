#include <iostream>
#include <string.h>
#include <cmath>
#include "../headers/DataCollector.h"

float DataCollector::getReactivePower() {

    // Обчислення φ із коефіцієнта потужності (φ = arccos(cos(φ)))
    float phi = std::acos(getPowerFactor());

    // Q = V * I * sin(φ)
    float reactivePower = getVoltage() * getCurrent() * std::cos(phi);
    return reactivePower;
}
