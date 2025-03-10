#include <iostream>
#include <string.h>
#include <thread>
#include "../lib/Server.h"
#include "../lib/Daemon.h"

void startServer(Server& server) {
    server.start();
}

int main(){
    Server server;

    Daemon daemon;
    daemon.addToStartup();
    // daemon.removeFromAutostart();
    daemon.backgroundMode();

    std::thread serverThread(startServer, std::ref(server));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "\033[1m\033[35m˚｡⋆\033[36mWelcome to the Server!\033[35m⋆｡˚\033[0m\n" << std::endl;

    // для додатку
    while (true) {
        std::string adminPassword;
        std::printf("Enter MySql root password: ");
        std::cin >> adminPassword;
        std::cin.ignore();

        server.setAdminPassword(adminPassword);
        server.CreateTable();
        break;
    }

    // для користувача
    while (true) {
        std::string answer;
        std::printf("|\033[37mRegister - 1 \033[0m|   |\033[37mLogin - 2 \033[0m|");
        std::cin >> answer;
        std::cin.ignore();

        if (answer == "1") {
            while (true) {
                std::printf("|\033[37mRegister as User - 1 \033[0m|   |\033[37mRegister as Admin - 2 \033[0m|");
                std::cin >> answer;
                std::cin.ignore();

                if (answer == "1") {
                    std::string Login, Password;
                    std::printf("Enter User Login: ");
                    std::cin >> Login;
                    std::printf("Enter User Password: ");
                    std::cin >> Password;
                    server.setName(Login);
                    server.setPassword(Password);
                    server.registerAsUser();
                    server.getAllUsersFromDB();
                    break;
                } else if (answer == "2") {
                    std::string Login, Password;
                    std::printf("Enter Admin Login: ");
                    std::cin >> Login;
                    std::printf("Enter Admin Password: ");
                    std::cin >> Password;
                    server.setName(Login);
                    server.setPassword(Password);
                    server.registerAsAdmin();
                    server.getAllAdminsFromDB();
                    break;
                }
            }
        } else if (answer == "2") {
            std::string Login, Password;
            std::printf("Enter Login name: ");
            std::cin >> Login;
            std::printf("Enter password: ");
            std::cin >> Password;

            server.setName(Login);
            server.setPassword(Password);

            if (server.Login()) {
                std::cout << "Login successful! Welcome, " << Login << "!" << std::endl;

                if (server.isAdministrator()) {
                    while (true) {
                        std::string answerMenu;
                        std::string menu = "|\033[37m Create record - 2 \033[0m|   |\033[37m Delete record - 3 \033[0m|\n";
                        menu += "|\033[37mView records - 4 \033[0m|   |\033[37m Create backup - 5 \033[0m|   |\033[37m View all users - 6 \033[0m|\n";
                        menu += "|\033[37mSet Phone Number - 7 \033[0m|   |\033[37m Set Email - 8 \033[0m|\n";
                        std::cout << menu;
                        std::cin >> answerMenu;

                        if (answerMenu == "2") {
                            std::cout << "Database for " + server.getCurrentDateTime() + " = " << std::endl;
                            server.setData();
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
                            printf("Admins: \n");
                            std::string adminsData = server.getAllAdminsFromDB();
                            std::cout << adminsData << std::endl;

                            printf("Users: \n");
                            std::string usersData = server.getAllUsersFromDB();
                            std::cout << usersData << std::endl;

                        } else if (answerMenu == "7"){
                            std::string phoneNumber;
                            printf("Enter Phone Number \n");
                            std::cin >> phoneNumber;
                            std::cin.ignore();
                            std::string uid = server.getUID();
                            server.setPhoneNumber(uid, phoneNumber);
                            printf("Your profile:\n");
                            server.getUserData();
                        } else if (answerMenu == "8"){
                            std::string email;
                            printf("Enter Email: \n");
                            std::cin >> email;
                            std::cin.ignore();
                            std::string uid = server.getUID();
                            server.setEmail(uid, email);
                            printf("Your profile:\n");
                            server.getUserData();
                        }
                    }
                } else {
                    while (true) {
                        std::string answerMenu;
                        std::string menu = "|\033[37mCreate record - 2 \033[0m|   |\033[37mView records - 4 \033[0m|\n";
                        menu += "|\033[37mCreate backup - 5 \033[0m|   |\033[37mSet Phone Number - 6 \033[0m|   |\033[37mSet Email - 7 \033[0m|\n";
                        std::cout << menu;
                        std::cin >> answerMenu;

                        if (answerMenu == "2") {
                            std::cout << "Database for " + server.getCurrentDateTime() + " = " << std::endl;
                            server.setData();
                        } else if (answerMenu == "4") {
                            std::cout << server.getData() << std::endl;
                        } else if (answerMenu == "5") {
                            server.createBackup();
                        } else if (answerMenu == "6"){
                            std::string phoneNumber;
                            printf("Enter Phone Number \n");
                            std::cin >> phoneNumber;
                            std::cin.ignore();
                            std::string uid = server.getUID();
                            server.setPhoneNumber(uid, phoneNumber);
                            printf("Your profile:\n");
                            server.getUserData();
                        } else if (answerMenu == "7"){
                            std::string email;
                            printf("Enter Email: \n");
                            std::cin >> email;
                            std::cin.ignore();
                            std::string uid = server.getUID();
                            server.setEmail(uid, email);
                            printf("Your profile:\n");
                            server.getUserData();
                        }
                    }
                }
            } else {
                std::cerr << "Login failed! Please check your credentials." << std::endl;
            }
        }

        // Запит на продовження роботи
        char continueChoice;
        std::cout << "Do you want to continue? (y/n): ";
        std::cin >> continueChoice;
        if (continueChoice != 'y' && continueChoice != 'Y') break;
    }

    // Закриваємо сервер
    serverThread.join(); 

    return 0;
}