#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include "Database.h"

// http://localhost:8080/api/data

class Server : public Database{
private:
    int port;

public:
    Server();
    ~Server();
    void handleClient(int clientSocket);

    void start();

};

#endif