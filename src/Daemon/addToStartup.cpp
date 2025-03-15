#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "../../lib/Daemon.h"

// sudo systemctl daemon-reload

// sudo systemctl restart SensorDaemon.service

// sudo systemctl status SensorDaemon.service

// Додавання до автозапуску
void Daemon::addToStartup() {
    if (servicePath.empty()) {
        std::string errorMessage = "Error: servicePath is empty!\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        return;
    }

    std::ofstream serviceFile(servicePath, std::ios::out | std::ios::trunc);
    if (!serviceFile) {
        std::string errorMessage = "Could not open " + servicePath + " for writing.\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        return;
    }

    // Отримуємо домашній шлях користувача (для підтримки ~)
    // const char* homeDir = getenv("HOME");
    // if (homeDir == nullptr) {
    //     std::string errorMessage = "Error: Unable to find home directory!\n";
    //     std::cerr << errorMessage;
    //     logError(errorMessage);
    //     return;
    // }

    serviceFile << "[Unit]\n";
    serviceFile << "Description=SensorDaemon\n";
    serviceFile << "After=network.target\n\n";

    serviceFile << "[Service]\n";
    serviceFile << "ExecStart=/home/admin1/Стільниця/Coliseum-project/build/start\n";
    serviceFile << "Restart=always\n";
    serviceFile << "User=root\n";
    serviceFile << "WorkingDirectory=/\n\n";

    serviceFile << "[Install]\n";
    serviceFile << "WantedBy=multi-user.target\n";

    serviceFile.close();

    // Оновлення systemd
    int reloadStatus = system("sudo systemctl daemon-reload");
    if (reloadStatus != 0) {
        std::cerr << "Error: Failed to reload systemd daemon!" << std::endl;
        logError("Error: Failed to reload systemd daemon!");
        return;
    }

    // Включення автозапуску
    int enableStatus = system("sudo systemctl enable SensorDaemon.service");
    if (enableStatus != 0) {
        std::string errorMessage = "Error: Failed to enable SensorDaemon service!\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        return;
    }

    std::cout << "\033[1m\033[33mDaemon added to autostart!\033[0m" << std::endl;
}
