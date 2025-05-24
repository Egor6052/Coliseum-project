#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Accounts.h"
#include <nlohmann/json.hpp>

bool Accounts::isAdministrator(std::string value_uid) {
    try {
        std::string userDataJson = getUserData(value_uid);
        nlohmann::json userData = nlohmann::json::parse(userDataJson);

        if (userData.contains("error")) {
            std::cerr << "Error in user data: " << userData["error"] << std::endl;
            logError("Error in user data: " + userData["error"].get<std::string>());
            return false;
        }

        std::string user_role = userData.contains("role") ? userData["role"].get<std::string>() : "";
        return user_role == "administrator";

    } catch (const std::exception& e) {
        std::cerr << "Error parsing user data: " << e.what() << std::endl;
        logError("Error parsing user data: " + std::string(e.what()));
        return false;
    }
}