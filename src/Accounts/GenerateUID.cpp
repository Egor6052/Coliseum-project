#include "../../lib/Accounts.h"
#include <string.h>
#include <iostream>
#include <random>
#include <ctime>
#include <sstream>

std::string Accounts::generateUID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream uid;
    for (int i = 0; i < 8; ++i) {
        uid << std::hex << dis(gen);
    }
    return uid.str();
}