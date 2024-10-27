#include "./SensorDataRepository.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>

int SensorDataRepository::count = 0;

SensorDataRepository::SensorDataRepository() {
    count++;
    id = count;

    activePower = 0.0f;
    reactivePower = 0.0f;

    current = 0.0f;
    voltage = 0.0f;
    ipAddress = "";
    nameSensor = "NoName";
    timestamp = "";
}

void SensorDataRepository::saveData(float currentValue, float voltageValue, float activePowerValue, float reactivePowerValue, std::string& nameValue) {

    if (currentValue >= 0) {
        current = currentValue;
    } else {
        throw std::invalid_argument("Current value cannot be negative.");
    }

    if (voltageValue >= 0) {
        voltage = voltageValue;
    } else {
        throw std::invalid_argument("Voltage value cannot be negative, or value is not found.");
    }

    if (activePowerValue >= 0) {
        activePower = activePowerValue;
    } else {
        throw std::invalid_argument("ActivePower value cannot be negative, or value is not found.");
    }

    if (reactivePowerValue >= 0) {
        reactivePower = reactivePowerValue;
    } else {
        throw std::invalid_argument("ReactivePower value cannot be negative, or value is not found.");
    }

    if (!nameValue.empty()) {
        nameSensor = nameValue;
    } else {
        throw std::invalid_argument("Name value is null.");
    }
}

// Метод для отримання поточного часу у форматі ISO 8601
std::string SensorDataRepository::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%SZ");
    return ss.str();
}

nlohmann::json SensorDataRepository::toJson() const {
    nlohmann::json jsonData;
    jsonData["timestamp"] = timestamp;
    jsonData["nameSensor"] = nameSensor;
    jsonData["current"] = current;
    jsonData["voltage"] = voltage;
    jsonData["activePower"] = activePower;
    jsonData["reactivePower"] = reactivePower;
    jsonData["ipAddress"] = ipAddress;
    return jsonData;
}

// Метод збереження JSON об'єкта у файл
bool SensorDataRepository::saveToJsonFile() const {

    try {
        // Генерація назви файлу з поточної дати
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d_%m_%Y", &tm);

        // TODO
        std::string filePath = "./database/" + std::string(buffer) + ".json";

        // Читання існуючого файлу або створення нового JSON об'єкта
        nlohmann::json rootJson;
        std::ifstream inFile(filePath);
        if (inFile.is_open()) {
            inFile >> rootJson;
            inFile.close();
        }

        // Додавання нового запису в форматі `data chunk { sensor1 {...}, sensor2 {...} }`
        rootJson["data chunk"][ipAddress] = toJson();

        // Запис JSON у файл
        std::ofstream outFile(filePath);
        if (outFile.is_open()) {
            outFile << rootJson.dump(4); // З відступами для зручності читання
            outFile.close();
            std::cout << "Data saved to " << filePath << std::endl;
            return true;
        } else {
            std::cerr << "Could not open file for writing: " << filePath << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error saving to JSON file: " << e.what() << std::endl;
        return false;
    }
}
