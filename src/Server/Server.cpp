#include <iostream>
#include <string>

#include "../headers/Server.h"

Server::Server() {
    this->configFilePath = "../config/configFile.conf";
    this->port = 5173;
    this->ip = "127.0.0.0";
    this->host_name = "localhost";

    Configuration();
}

Server::~Server() { 

}
