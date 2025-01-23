#include "Server.h"
#include <iostream>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Server::Server() {
    this->port = 8080;
}

Server::~Server() {}

void Server::handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    //Reading data from the client
    read(clientSocket, buffer, sizeof(buffer) - 1);

    // Sending reply
    std::string response =
        // "HTTP/1.1 200 OK\r\n"
        // "Content-Type: text/plain\r\n"
        // "Connection: close\r\n"
        // "\r\n"
        getData();
    send(clientSocket, response.c_str(), response.size(), 0);
    close(clientSocket);
}

void Server::start() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Unable to create socket.\n";
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Unable to bind socket to port.\n";
        close(serverSocket);
        return;
    }

    // We start listening to the connection
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Error: Unable to listen on socket.\n";
        close(serverSocket);
        return;
    }

    // http://localhost:8080/api/data

    std::cout << "The HTTP server is running...\n";
    std::cout << "\033[32m http://localhost:" << port << "/api/data \033[0m\n";

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        if (clientSocket == -1) {
            std::cerr << "Error: Unable to accept connection.\n";
            continue;
        }

        // We process the client connection in a new thread
        std::thread(&Server::handleClient, this, clientSocket).detach();
    }

    close(serverSocket);
}
