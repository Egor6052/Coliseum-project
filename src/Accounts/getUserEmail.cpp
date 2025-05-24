#include "../headers/Accounts.h"
#include <iostream>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>

std::string Accounts::getUserEmail(const std::string& uid) {
    try {
        std::string userDataJson = getUserData(uid);
        nlohmann::json userData = nlohmann::json::parse(userDataJson);

        if (userData.contains("error")) {
            std::cerr << "Error in user data: " << userData["error"] << std::endl;
            logError("Error in user data: " + userData["error"].get<std::string>());
            return "";
        }

        return userData.value("email", "");
    } catch (const std::exception& e) {
        std::cerr << "Error parsing user data: " << e.what() << std::endl;
        logError("Error parsing user data: " + std::string(e.what()));
        return "";
    }
}
