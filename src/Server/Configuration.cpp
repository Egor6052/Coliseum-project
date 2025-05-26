#include <fstream>
#include <sstream>
#include <map>
#include <string>
// #include <unordered_map>
#include <algorithm>

#include "../headers/Server.h"

static inline std::string trim(const std::string& s) {
    std::string str = s;
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    return str;
}

void Server::Configuration() {
    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        std::cerr << "Could not open configuration file: " << configFilePath << "\n";
        logError("Could not open configuration file: " + configFilePath + "\n");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Ігноруємо коментарі та порожні рядки
        if (line.empty() || line[0] == '#') continue;

        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                // Обрізаємо пробіли з ключа та значення
                key = trim(key);
                value = trim(value);
                configValues[key] = value;
            }
        }
    }

    file.close();


    ConfigFields();
    std::cout << "Configuration finished!" << std::endl;
}

void Server::ConfigFields() {
    std::map<std::string, int*> configMap = {
        {"port", &port}
    };

    for (const auto& [key, variable] : configMap) {
        if (configValues.find(key) != configValues.end()) {
            try {
                *variable = std::stoi(configValues[key]); // Обробка помилок для чисел
            } catch (const std::exception& e) {
                std::cerr << "Error converting " << key << " value '" << configValues[key] << "' to integer: " << e.what() << "\n";
                logError("Error converting " + key + " value '" + configValues[key] + "' to integer: " + e.what());
            }
        }
    }

    std::map<std::string, std::string*> dumpMap = {
        {"ip", &ip}
    };

    for (const auto& [key, variable] : dumpMap) {
        if (configValues.find(key) != configValues.end()) {
            *variable = configValues[key];
        }
    }
}