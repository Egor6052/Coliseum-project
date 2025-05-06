#include <iostream>
#include <string>

#include "../headers/Server.h"

Server::Server() {
    this->configFilePath = "../config/configFile.conf";
    this->port = 5173;
    this->ip = "127.0.0.0";
    this->host_name = "localhost";

    this->keyAccess = "jD7vn1DiXMrEJaJF02/8s8Eg/CVMl+CkD+qNxEntERU=";
    this->keyRefresh = "Wyg5/fnpE9Mp1sx9qbr6EFTkCAcr8QMfhMAkuKsALck=";
    
    Configuration();
}

Server::~Server() { 

}

std::string Server::getKeyAccess(){
    return keyAccess;
}

std::string Server::getKeyRefresh(){
    return keyRefresh;
}
