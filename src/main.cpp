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

    server.setAdminPassword(adminPassword);
    server.createMySQLUser();
    server.CreateTable();

    do {
        std::string menu, answer;
        menu = "|\033[37mStart server - 1 \033[0m|   |\033[37m Create record - 2 \033[0m|  |\033[37m Delete record - 3 \033[0m|   |\033[37m View records - 4 \033[0m|   |\033[37m Create backup - 5 \033[0m|\n";
        menu += "   |\033[37m Create User - 6 \033[0m|   |\033[37m Create Admin - 7 \033[0m|   |\033[37m View All Users - 8 \033[0m|   |\033[37m View All Admins - 9 \033[0m|";

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
        } else if (answer == "6"){
            std::string Login, Password;
            std::printf("Enter User Login: ");
            std::cin >> Login;
            std::printf("Enter User Password: ");
            std::cin >> Password;
            server.setName(Login);
            server.setPassword(Password);
            server.registerAsUser();

            server.getAllUsersFromDB();

        } else if (answer == "7"){
            std::string Login, Password;
            std::printf("Enter Admin Login: ");
            std::cin >> Login;
            std::printf("Enter Admin Password: ");
            std::cin >> Password;
            server.setName(Login);
            server.setPassword(Password);
            server.registerAsAdmin();
            
            server.getAllAdminsFromDB();

        } else if (answer == "8"){
            server.getAllUsersFromDB();
        } else if (answer == "9"){
            server.getAllAdminsFromDB();
        }
    } while (true);

    return 0;
}