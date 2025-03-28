#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "../headers/Server.h"

// TODO
void Server::createCSV(const std::string& filename) {
    std::string directory = "./emails";
    std::string fullPath = directory + "/" + filename;

    // Перевіряємо, чи існує директорія, якщо ні — створюємо
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    std::ofstream file(fullPath);
    if (!file.is_open()) {
        std::string massageError = "Could not open file for writing: " + fullPath;
        std::cerr << massageError << std::endl;
        logError(massageError);
        return;
    }

    // TODO
    // Заголовки таблиці
    file << "Ім'я, Вік, Місто\n";

    // Дані
    std::vector<std::vector<std::string>> data = {
        {"Іван", "25", "Київ"},
        {"Марія", "30", "Львів"},
        {"Олег", "22", "Одеса"}
    };

    for (const auto& row : data) {
        file << row[0] << "," << row[1] << "," << row[2] << "\n";
    }

    file.close();
    std::cout << "File " << fullPath << " created successfully!" << std::endl;
}
