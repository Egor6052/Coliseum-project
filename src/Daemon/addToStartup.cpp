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
        std::cerr << "Error: servicePath is empty!" << std::endl;
        logError("Error: servicePath is empty!");
        return;
    }

    std::ofstream serviceFile(servicePath, std::ios::out | std::ios::trunc);
    if (!serviceFile) {
        std::cerr << "Could not open " << servicePath << " for writing." << std::endl;
        logError("Could not open " << servicePath << " for writing.");
        return;
    }

    // Отримуємо домашній шлях користувача (для підтримки ~)
    const char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        std::cerr << "Error: Unable to find home directory!" << std::endl;
        logError("Error: Unable to find home directory!");
        return;
    }

    serviceFile << "[Unit]\n";
    serviceFile << "Description=SensorDaemon\n";
    serviceFile << "After=network.target\n\n";

    serviceFile << "[Service]\n";
    serviceFile << "ExecStart=" + std::string(homeDir) + "/Documents/Coliseum-project/build/start\n";
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
        std::cerr << "Error: Failed to enable SensorDaemon service!" << std::endl;
        logError("Error: Failed to enable SensorDaemon service!");
        return;
    }

    std::cout << "\033[1m\033[33mDaemon added to autostart!\033[0m" << std::endl;
}
