#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <filesystem>

#include "../headers/Daemon.h"

Daemon::Daemon(){
    this->servicePath = "/etc/systemd/system/SensorDaemon.service";
    this->configFilePath = absolutePath() + "/config/configFile.conf";
    this->program_path = absolutePath() + "/build/start";
    this->working_directory = absolutePath();
}

Daemon::~Daemon(){  }

// TODO integration with windows

std::string Daemon::absolutePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        auto path = std::filesystem::path(std::string(result, count));
        return path.parent_path().parent_path().string();
    } else {
        return "";
    }
}