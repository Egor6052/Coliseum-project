#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include "Database.h"

class Server : public Database {
private:
    int port;

public:
    Server();
    ~Server();
    void handleClient(int clientSocket);

    void RS485();
    void start();

};

#endif