#include <iostream>
#include <string.h>
#include <cmath>
#include "../lib/Database.h"

float Database::getActivePower() {

    // P = V * I * cos(φ)
    // getPowerFactor() - Коефіцієнт потужності (cos(φ))

    // Якщо значення ϕ задається в градусах, потрібно конвертувати його в радіани
    // float radians = degrees * M_PI / 180.0f;
    // float activePower =  getVoltage() *  getCurrent() * std::cos(radians);

    float activePower = getVoltage() * getCurrent() * std::cos(getPowerFactor());
    return activePower;
}