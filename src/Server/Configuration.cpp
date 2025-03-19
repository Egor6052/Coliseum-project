#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <unordered_map>

#include "../headers/Server.h"

void Server::Configuration() {

    std::ifstream file(configFilePath);
    if (!file) {
        std::cerr << "Could not open configuration file: " << configFilePath << "\n";
        logError("Could not open configuration file: " + configFilePath + "\n");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Ignore comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                configValues[key] = value;
            }
        }
    }

    // Updating variables from configuration
    if (configValues.find("can_path") != configValues.end()) {
        this->can_path = configValues["can_path"];
    }

    ConfigFields();
    std::cout << "Configuration finished!" << std::endl;
}

void Server::ConfigFields() {
    std::map<std::string, int*> configMap = {
        {"seakeeperSystemAll", &seakeeperSystemAll},
        {"seakeeperGyroStab", &seakeeperGyroStab},
        {"ing_left_power", &ing_left_power},
        {"ing_right_power", &ing_right_power},
        {"engine_right", &engine_right},
        {"engine_left", &engine_left},
        {"trim_left_engine_UP", &trim_left_engine_UP},
        {"trim_left_engine_DOWN", &trim_left_engine_DOWN},
        {"trim_right_engine_UP", &trim_right_engine_UP},
        {"trim_right_engine_DOWN", &trim_right_engine_DOWN},
        {"trim_general_UP", &trim_general_UP},
        {"trim_general_DOWN", &trim_general_DOWN},
        {"starlink_On_Off", &starlink_On_Off},
        {"kamet_On_Off", &kamet_On_Off},
        {"timeout", &timeout},
        {"operatingFrequency", &operatingFrequency}
    };

    for (const auto& [key, variable] : configMap) {
        if (configValues.find(key) != configValues.end()) {
            *variable = std::stoi(configValues[key]);
        }
    }

    std::map<std::string, std::string*> dumpMap = {
        {"seakeeperSystemAll_on_dump", &seakeeperSystemAll_on_dump},
        {"seakeeperSystemAll_off_dump", &seakeeperSystemAll_off_dump},
        {"seakeeperGyroStab_on_dump", &seakeeperGyroStab_on_dump},
        {"seakeeperGyroStab_off_dump", &seakeeperGyroStab_off_dump},
        {"ing_left_power_on_dump", &ing_left_power_on_dump},
        {"ing_left_power_off_dump", &ing_left_power_off_dump},
        {"ing_right_power_on_dump", &ing_right_power_on_dump},
        {"ing_right_power_off_dump", &ing_right_power_off_dump},
        {"engine_right_on_dump", &engine_right_on_dump},
        {"engine_right_off_dump", &engine_right_off_dump},
        {"engine_left_on_dump", &engine_left_on_dump},
        {"engine_left_off_dump", &engine_left_off_dump},
        {"trim_left_engine_UP_on_dump", &trim_left_engine_UP_on_dump},
        {"trim_left_engine_UP_off_dump", &trim_left_engine_UP_off_dump},
        {"trim_left_engine_DOWN_on_dump", &trim_left_engine_DOWN_on_dump},
        {"trim_left_engine_DOWN_off_dump", &trim_left_engine_DOWN_off_dump},
        {"trim_right_engine_UP_on_dump", &trim_right_engine_UP_on_dump},
        {"trim_right_engine_UP_off_dump", &trim_right_engine_UP_off_dump},
        {"trim_right_engine_DOWN_on_dump", &trim_right_engine_DOWN_on_dump},
        {"trim_right_engine_DOWN_off_dump", &trim_right_engine_DOWN_off_dump},
        {"trim_general_UP_on_dump", &trim_general_UP_on_dump},
        {"trim_general_UP_off_dump", &trim_general_UP_off_dump},
        {"trim_general_DOWN_on_dump", &trim_general_DOWN_on_dump},
        {"trim_general_DOWN_off_dump", &trim_general_DOWN_off_dump},
        {"starlink_On_Off_on_dump", &starlink_On_Off_on_dump},
        {"starlink_On_Off_off_dump", &starlink_On_Off_off_dump},
        {"kamet_On_Off_on_dump", &kamet_On_Off_on_dump},
        {"kamet_On_Off_off_dump", &kamet_On_Off_off_dump}
    };

    for (const auto& [key, variable] : dumpMap) {
        if (configValues.find(key) != configValues.end()) {
            *variable = configValues[key];
        }
    }
}