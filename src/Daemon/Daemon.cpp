#include <filesystem>
#include <string>
#include <unistd.h>
#include <limits.h>


#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

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

#if defined(__linux__)
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        return std::filesystem::path(std::string(result, count)).parent_path().parent_path().string();
    }

#elif defined(__APPLE__)
    uint32_t size = sizeof(result);
    if (_NSGetExecutablePath(result, &size) == 0) {
        return std::filesystem::path(result).parent_path().parent_path().string();
    }
#endif

    return "";
}
