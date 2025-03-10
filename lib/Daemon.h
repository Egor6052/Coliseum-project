#pragma once

#include <iostream>
#include <string.h>

class Daemon {
    private:
        // "/etc/systemd/system/PiDaemon.service"
        std::string servicePath;

    public:
        Daemon();
        ~Daemon();

        void addToStartup();
        void removeFromAutostart();
        void backgroundMode();

};
