#include <iostream>
#include <string.h>
#include <thread>
#include "./headers/Server.h"
#include "./headers/Daemon.h"

int main() {
    Server server;
    Daemon daemon;

    std::cout << "\033[1m\033[35m˚｡⋆\033[36mWelcome to the Server!\033[35m⋆｡˚\033[0m\n" << std::endl;

    daemon.addToStartup();
    server.http_start();

    server.setAdminPassword("MySqlStrongPassword123!");
    server.CreateTable();

    // Запускаємо dataCollector у окремому потоці з періодичністю 1 хвилина
    std::thread collectorThread([&server]() {
        while (true) {
            server.dataCollector();
            std::this_thread::sleep_for(std::chrono::minutes(1)); // Затримка 1 хвилина
        }
    });

    // Від’єднуємо потік, щоб він працював незалежно
    collectorThread.detach();

    // Основний потік просто чекає
    std::cout << "Server is running in \033[1m\033[35mhttp://localhost:8080/\033[36m. Use HTTP endpoints to interact. Press Ctrl+C to exit." << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::hours(24));
    }

    return 0;
}