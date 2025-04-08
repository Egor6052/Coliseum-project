#pragma once

#include <iostream>
#include <string.h>
#include "Logger.h"

class Daemon : public Logger {
    private:
        // "/etc/systemd/system/SensorDaemon.service"
        std::string configFilePath;
        std::string servicePath;
        std::string program_path;
        std::string working_directory;
        std::string absolutePath();

    public:
        Daemon();
        ~Daemon();

        void addToStartup();
        void removeFromAutostart();
        // void backgroundMode();

};
