#include "../headers/Daemon.h"

// Remove from autostart
void Daemon::removeFromAutostart() {
    system("systemctl disable SensorDaemon.service");
    system("rm -f /etc/systemd/system/SensorDaemon.service");
    system("systemctl daemon-reload");

    std::cout << "\033[1m\033[32mDaemon has been removed from autostart!\033[0m" << std::endl;
}