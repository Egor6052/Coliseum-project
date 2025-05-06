
#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>


// Обробка запиту для виходу
void Server::shandleLogoutRequest(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано POST-запит до /logout: " << req.body << std::endl;

    // Логіка виходу (наразі просто повертаємо успіх)
    Json::Value response;
    response["message"] = "Logout successful";

    Json::StreamWriterBuilder writer;
    std::string responseStr = Json::writeString(writer, response);
    std::cout << "Response: " << responseStr << std::endl;

    res.set_content(responseStr, "application/json");
}

// Обробка запиту для виходу з усіх сесій
void Server::handleLogoutAllRequest(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано POST-запит до /logoutall: " << req.body << std::endl;

    // Логіка виходу з усіх сесій (наразі просто повертаємо успіх)
    Json::Value response;
    response["message"] = "Logout from all sessions successful";

    Json::StreamWriterBuilder writer;
    std::string responseStr = Json::writeString(writer, response);
    std::cout << "Response: " << responseStr << std::endl;

    res.set_content(responseStr, "application/json");
}
