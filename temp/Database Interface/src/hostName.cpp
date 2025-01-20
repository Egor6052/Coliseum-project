#include <iostream>
#include <string.h>
#include "../lib/User.h"

void User::setHostName(std::string hostNameValue) {
    if (!hostNameValue.empty() && hostNameValue.length() <= 50) {
        this->hostName = hostNameValue;
    } else {
        std::cerr << "Invalid host name. It must not be empty and should not exceed 50 characters.\n";
    }
}

std::string User::getHostName(){
    return this->hostName;
}