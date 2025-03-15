#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include "Database.h"

class Server : public Database {
private:
    int port;
    std::string host_name;

public:
    Server();
    ~Server();
    void handleClient(int clientSocket);
    
    // Retrieving the request body
    std::string getRequestBody(const std::string& request);

    // Getting a parameter from the request body
    std::string extractParameter(const std::string& body, const std::string& param);

    void RS485();
    void start();

};

#endif