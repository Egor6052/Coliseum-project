// TODO

#include <iostream>
#include <cstdlib>
#include "../headers/Server.h"

void Server::sendToEmail(const std::string& recipient, const std::string& filename) {
    std::string command = "echo 'Дивіться вкладений файл' | mutt -s 'Таблиця' -a " + filename + " -- " + recipient;
    int result = system(command.c_str());

    if (result != 0) {
        std::string massageError = "Error sending email!";
        std::cerr << massageError << std::endl;
        logError(massageError);
    } else {
        std::cout << "Email sent to: " << recipient << std::endl;
    }
}
