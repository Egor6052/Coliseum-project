#include <iostream>
#include <string.h>
#include <thread>
#include "./headers/Server.h"
#include "./headers/Daemon.h"
#include "./headers/Accounts.h"

#include "./headers/DataCollector.h"

int main() {
    Server server;
    Daemon daemon;
    Accounts account;
    Database db;
    DataCollector dataCollector;

    std::cout << "\033[1m\033[35m˚｡⋆\033[36mWelcome to the Server!\033[35m⋆｡˚\033[0m\n" << std::endl;
    db.setAdminPassword("MySqlStrongPassword123!");
    db.createDB();
    db.CreateTable();
    daemon.addToStartup();
    server.http_start();
    // account.handleLoginFromAPI();


    // Run it in a separate thread with periodicity
    std::thread collectorThread([&dataCollector]() {
        while (true) {
            dataCollector.dataCollector();
            std::this_thread::sleep_for(std::chrono::hours(24));
        }
    });


    // Disconnecting the flow
    collectorThread.detach();

    // The main thread is just waiting.
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}