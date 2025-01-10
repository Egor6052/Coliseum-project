#include <iostream>
#include <string.h>
#include "../lib/User.h"

void User::CreateUser(std::string valueAnswer) {
    if (valueAnswer == "Y" || valueAnswer == "y") {
        std::cout << "Enter user name: ";
        std::string name, password;
        std::getline(std::cin, name);
        setUserName(name);

        std::cout << "Enter user password: ";
        std::getline(std::cin, password);
        setUserPassword(password);

        std::string command = "../bash/CreateUser.sh " + getUserName() + " " + getUserPassword();

        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "User created successfully!\n";
        } else {
            std::cerr << "Failed to create user.\n";
        }
    } else if (valueAnswer == "N" || valueAnswer == "n") {
        std::cout << "Exit!\n";
    } else {
        std::cerr << "Invalid input!\n";
    }
}