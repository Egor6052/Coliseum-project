#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../../lib/Daemon.h"

// Adding to autostart
void Daemon::addToStartup() {
    if (servicePath.empty()) {
        std::cerr << "Error: servicePath is empty!" << std::endl;
        return;
    }

    std::ofstream serviceFile(servicePath, std::ios::out | std::ios::trunc);
    if (!serviceFile) {
        std::cerr << "Could not open " << servicePath << " for writing." << std::endl;
        return;
    }

    serviceFile << "[Unit]\n";
    serviceFile << "Description=SensorDaemon\n";
    serviceFile << "After=network.target\n\n";
    serviceFile << "[Service]\n";
    serviceFile << "ExecStart=/usr/local/bin/SensorDaemon\n";
    serviceFile << "Restart=always\n";
    serviceFile << "User=root\n";
    serviceFile << "WorkingDirectory=/\n\n";
    serviceFile << "[Install]\n";
    serviceFile << "WantedBy=multi-user.target\n";
    
    serviceFile.close();

    // Updating systemd
    int reloadStatus = system("systemctl daemon-reload");
    if (reloadStatus != 0) {
        std::cerr << "Error: Failed to reload systemd daemon!" << std::endl;
        return;
    }

    // Enabling autorun
    int enableStatus = system("systemctl enable SensorDaemon.service");
    if (enableStatus != 0) {
        std::cerr << "Error: Failed to enable SensorDaemon service!" << std::endl;
        return;
    }

    std::cout << "\033[1m\033[33mDaemon added to autostart!\033[0m" << std::endl;
}