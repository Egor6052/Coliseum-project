#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

#include "../headers/Daemon.h"

// Додавання до автозапуску
void Daemon::addToStartup() {
    if (servicePath.empty()) {
        std::string errorMessage = "Error: servicePath is empty!\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        return;
    }

    // Відкриваємо файл для запису (перезаписуємо, якщо він існує)
    std::ofstream serviceFile(servicePath, std::ios::out | std::ios::trunc);
    if (!serviceFile) {
        std::string errorMessage = "Could not open " + servicePath + " for writing.\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        return;
    }

    serviceFile << "[Unit]\n";
    serviceFile << "Description=SensorDaemon\n";
    serviceFile << "After=network.target\n\n";

    serviceFile << "[Service]\n";
    serviceFile << "ExecStart=" + program_path + "\n";
    serviceFile << "Restart=always\n";
    serviceFile << "User=root\n";
    serviceFile << "WorkingDirectory=" + working_directory + "\n\n";

    serviceFile << "[Install]\n";
    serviceFile << "WantedBy=multi-user.target\n";

    serviceFile.close();
    // std::cout << "File created/overwritten: " << servicePath << std::endl;

    // Оновлення systemd
    int reloadStatus = system("sudo systemctl daemon-reload");
    // std::cout << "Daemon reloaded successful!" << std::endl;

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