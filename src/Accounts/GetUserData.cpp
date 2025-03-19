#include "../headers/Accounts.h"
#include <iostream>
#include <string>
#include <sstream>

std::string Accounts::getUserData() {
    std::stringstream json;
    json << "{"
            << "\"uid\": \"" << getUID() << "\", "
            << "\"name\": \"" << getUserName() << "\", "
            << "\"phone\": \"" << getUserPhoneNumber() << "\", "
            << "\"email\": \"" << getUserEmail() << "\""
            << "}";

    return json.str();
}
