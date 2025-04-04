#include <iostream>
#include <string.h>
#include <thread>
#include "./headers/Server.h"
#include "./headers/Daemon.h"

// void startServer(Server& server) {
//     server.start();
// }

int main(){
    Server server;
    Daemon daemon;

    std::cout << "\033[1m\033[35m˚｡⋆\033[36mWelcome to the Server!\033[35m⋆｡˚\033[0m\n" << std::endl;

    daemon.addToStartup();
    // daemon.removeFromAutostart();
    server.http_start();

    server.setAdminPassword("MySqlStrongPassword123!");
    server.CreateTable();
    server.dataCollector();

    // для користувача
    try {
        // server.run();
        
        std::string answer;
        std::printf("|\033[37mRegister - 1 \033[0m|   |\033[37mLogin - 2 \033[0m|");
        std::cin >> answer;
        std::cin.ignore();

        if (answer == "1") {
            while (true) {
                std::string role;
                std::printf("|\033[37mRegister as User - user \033[0m|   |\033[37mRegister as Admin - admin \033[0m|");
                std::cin >> role;
                std::cin.ignore();

                if (role == "user") {
                    std::string Login, Password, email;
                    std::printf("Enter User Login: ");
                    std::cin >> Login;
                    std::printf("Enter User Password: ");
                    std::cin >> Password;
                    std::printf("Enter User email: ");
                    std::cin >> email;

                    // server.setName(Login);
                    // server.setPassword(Password);
                    server.registerNewUser(Login, Password, email, role);
                    // TODO
                    // server.getAllUsers();
                    // server.registerAsUser();
                    // server.getAllUsersFromDB();
                    break;
                } else if (role == "admin") {
                    std::string Login, Password, email;
                    std::printf("Enter Admin Login: ");
                    std::cin >> Login;
                    std::printf("Enter Admin Password: ");
                    std::cin >> Password;
                    std::printf("Enter User email: ");
                    std::cin >> email;
                    // server.setName(Login);
                    // server.setPassword(Password);
                    server.registerNewUser(Login, Password, email, role);
                    // TODO getUserFromDB();
                    // server.getAllUsers();
                    // server.getAllAdminsFromDB();
                    break;
                }
            }
        } else if (answer == "2") {
            std::string Login, Password;
            std::printf("Enter Login name: ");
            std::cin >> Login;
            std::printf("Enter password: ");
            std::cin >> Password;

            if (server.Login(Login, Password)) {
                std::cout << "Login successful! Welcome, " << Login << "!" << std::endl;

                if (server.isAdministrator(Login, Password)) {
                    while (true) {
                        std::string answerMenu;
                        std::string menu = "|   |\033[37m Delete record - 3 \033[0m|\n";
                        menu += "|\033[37mView records - 4 \033[0m|   |\033[37m Create backup - 5 \033[0m|   |\033[37m View all users - 6 \033[0m|\n";
                        std::cout << menu;
                        std::cin >> answerMenu;

                        if (answerMenu == "2") {
                            std::cout << "Database for " + server.getCurrentDateTime() + " = " << std::endl;
                            // server.setData();
                        } else if (answerMenu == "3") {
                            std::cout << server.getData() << std::endl;
                            std::printf("Enter id record would you like to delete: ");
                            std::cin >> answerMenu;
                            std::cin.ignore();
                            server.deleteData(answerMenu);
                            std::cout << server.getData() << std::endl;
                        } else if (answerMenu == "4") {
                            std::cout << server.getData() << std::endl;
                        } else if (answerMenu == "5") {
                            server.createBackup();
                        } else if (answerMenu == "6") {
                            // printf("Admins: \n");
                            // std::string adminsData = server.getAllAdminsFromDB();
                            // std::cout << adminsData << std::endl;

                            printf("Users: \n");
                            std::string usersData = server.getAllUsersFromDB();
                            std::cout << usersData << std::endl;
                        }
                    }
                } else {
                    while (true) {
                        std::string answerMenu;
                        std::string menu = "|   |\033[37mView records - 4 \033[0m|\n";
                        menu += "|\033[37mCreate backup - 5 \033[0m|   \033[0m|\n";
                        std::cout << menu;
                        std::cin >> answerMenu;

                        if (answerMenu == "2") {
                            std::cout << "Database for " + server.getCurrentDateTime() + " = " << std::endl;
                            // server.setData();
                        } else if (answerMenu == "4") {
                            std::cout << server.getData() << std::endl;
                        } else if (answerMenu == "5") {
                            server.createBackup();
                        }
                    }
                }
            } else {
                std::cerr << "Login failed! Please check your credentials." << std::endl;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}