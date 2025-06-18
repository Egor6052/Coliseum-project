
#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

// Обробка всіх клієнтських маршрутів (повернення index.html)
void Server::handleClientRoutes(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Customer request received: " << req.path << std::endl;

    // Перевірка на статичні ресурси (.js, .css, .ico, .svg)
    if (req.path.size() >= 3 && req.path.substr(req.path.size() - 3) == ".js") {
        std::cout << "404: JavaScript file not found: " << req.path << std::endl;
        res.status = 404;
        res.set_content("JavaScript file not found", "text/plain");
        return;
    }
    if (req.path.size() >= 4 && req.path.substr(req.path.size() - 4) == ".css") {
        std::cout << "404: CSS file not found: " << req.path << std::endl;
        res.status = 404;
        res.set_content("CSS file not found", "text/plain");
        return;
    }
    if (req.path.size() >= 4 && req.path.substr(req.path.size() - 4) == ".ico") {
        std::cout << "404: Favicon file not found: " << req.path << std::endl;
        res.status = 404;
        res.set_content("Favicon file not found", "text/plain");
        return;
    }
    if (req.path.size() >= 4 && req.path.substr(req.path.size() - 4) == ".svg") {
        std::cout << "404: SVG file not found: " << req.path << std::endl;
        res.status = 404;
        res.set_content("SVG file not found", "text/plain");
        return;
    }

    // Перенаправлення для всіх маршрутів /client/error/*
    if (req.path.find("/client/error/") == 0) {
        std::cout << "Redirecting /client/error/* to /client" << std::endl;
        res.set_header("Location", "/client");
        res.status = 302; // Found
        return;
    }

    // Повернення index.html для SPA-маршрутів, включаючи /client
    std::ifstream file("/home/admin/Programs/Coliseum-project/client/dist/index.html");
    if (file) {
        std::cout << "Serving index.html for: " << req.path << std::endl;
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.set_content(buffer.str(), "text/html");
    } else {
        std::cout << "Error: index.html not found at /home/admin/Programs/Coliseum-project/client/dist/index.html" << std::endl;
        res.status = 404;
        res.set_content("index.html not found", "text/plain");
    }
}