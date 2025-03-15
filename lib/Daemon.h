#pragma once

#include <iostream>
#include <string.h>
#include "Logger.h"

class Daemon : public Logger {
    private:
        // "/etc/systemd/system/PiDaemon.service"
        std::string servicePath;

    public:
        Daemon();
        ~Daemon();

        void addToStartup();
        void removeFromAutostart();
        // void backgroundMode();

};
