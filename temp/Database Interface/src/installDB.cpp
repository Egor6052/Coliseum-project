#include <iostream>
#include <string.h>
#include "../lib/User.h"

void User::installDB(std::string valueAnswer) {
    if (valueAnswer == "Y" || valueAnswer == "y") {
        std::cout << "Installing database...\n";

        std::string command = "chmod +x ../bash/installDB.sh";

        int result = system("sudo ../bash/installDB.sh");
        if (result == 0) {
            printf("Database installed successfully!\n");
        } else {
            printf("Error during database installation.\n");
        }
    } else if (valueAnswer == "N" || valueAnswer == "n") {
        std::cout << "Exit!\n";
    } else {
        std::cerr << "Invalid input!\n";
    }
}