#include <iostream>
#include <string.h>
#include <cmath>
#include "../lib/Database.h"

float Database::getReactivePower() {

    // Обчислення φ із коефіцієнта потужності (φ = arccos(cos(φ)))
    float phi = std::acos(getPowerFactor());

    // Q = V * I * sin(φ)
    float reactivePower = getVoltage() * getCurrent() * std::sin(phi);
    return reactivePower;
}
