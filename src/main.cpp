#include <iostream>
#include <string.h>
#include "../lib/Server.h"

int main(){
    Server server;

    std::cout << "\033[1m\033[35m˚｡⋆\033[36mWelcome to the Server!\033[35m⋆｡˚\033[0m\n" << std::endl;
    std::string adminPassword;
    std::printf("Enter MySql admin password: ");
    std::cin >> adminPassword;
    std::cin.ignore();

    server.createMySQLUser(adminPassword);
    server.CreateTable();

    do {
        std::string menu, answer;
        menu = "|\033[37mStart server - 1 \033[0m|   |\033[37m Create record - 2 \033[0m|  |\033[37m Delete record - 3 \033[0m|   |\033[37m View records - 4 \033[0m|   |\033[37m Create backup - 5 \033[0m|";

        std::string horizontalLine(menu.length()-45, '-');
        std::cout << horizontalLine << "\n" << menu << "\n" << horizontalLine << std::endl;
        
        std::cin >> answer;
        std::cin.ignore();

        if (answer == "1"){
            server.start();
            server.handleClient(1212);
        } else if (answer == "2") {
            std::cout << "Database for " + server.getCurrentDateTime() + " = " << std::endl;
            server.setData();
        } else if (answer == "3"){
            std::cout << server.getData() << std::endl;
            std::printf("Enter id record would you like to delete: ");
            std::cin >> answer;
            std::cin.ignore();
            server.deleteData(answer);
            std::cout << server.getData() << std::endl;
        } else if (answer == "4"){
            std::cout << server.getData() << std::endl;
        } else if (answer == "5"){
            server.createBackup();
        }
    } while (true);

    return 0;
}