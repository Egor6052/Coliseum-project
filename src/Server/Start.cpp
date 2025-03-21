#include <iostream>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../headers/Server.h"

void Server::start() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Unable to create socket.\n";
        logError("Error: Unable to create socket.\n");
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Прив'язуємо сокет до порту
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Unable to bind socket to port.\n";
        logError("Error: Unable to bind socket to port.\n");
        close(serverSocket);
        return;
    }

    // Слухаємо підключення
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Error: Unable to listen on socket.\n";
        logError("Error: Unable to listen on socket.\n");
        close(serverSocket);
        return;
    }

    // Повідомлення про запуск сервера
    std::cout << "The HTTP server is running...\n";
    std::cout << "\033[32m http://" << host_name << ":" << port << "/api/data \033[0m\n";

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientSize = sizeof(clientAddr);
        // int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        // if (clientSocket == -1) {
        //     std::cerr << "Error: Unable to accept connection.\n";
        //     logError("Error: Unable to accept connection.\n");
        //     continue;
        // }

        // Обробляємо підключення в новому потоці
        // std::thread(&Server::handleClient, this, clientSocket).detach();
    }

    close(serverSocket);
}
