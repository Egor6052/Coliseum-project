
#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

// Обробка всіх клієнтських маршрутів (повернення index.html)
void Server::handleClientRoutes(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Customer request received: " << req.path << std::endl;

    // Перенаправлення для всіх маршрутів /client/error/*
    if (req.path.find("/client/error/") == 0) {
        res.set_header("Location", "/");
        res.status = 302; // Found
        return;
    }
    std::ifstream file("../client/dist/index.html");
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.set_content(buffer.str(), "text/html");
    } else {
        res.status = 404;
        res.set_content("index.html not found", "text/plain");
    }
}
