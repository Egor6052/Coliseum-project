#include <iostream>
#include "../lib/Database.h"
#include <cmath>

float Database::roundNumber(float valueNumber) {
    float rounded = std::round(valueNumber * 1000.0f) / 1000.0f;
    return rounded;
}