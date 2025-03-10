#include "../../lib/Daemon.h"

Daemon::Daemon(){
    this->servicePath = "/etc/systemd/system/SensorDaemon.service";
}

Daemon::~Daemon(){  }

