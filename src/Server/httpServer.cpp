#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

void Server::http_start() {
    // Запускаємо два сервери в окремих потоках
    std::thread static_thread(&Server::startStaticServer, this);
    std::thread api_thread(&Server::startApiServer, this);

    // Чекаємо завершення потоків
    static_thread.join();
    api_thread.join();
}

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "<h1>404 Not Found</h1>";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Server::startStaticServer() {
    httplib::Server server;

    server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        std::string content = readFile("../client/dist/index.html");

        res.set_content(content, "text/html; charset=UTF-8");
    });

    std::cout << "Сервер запущено на http://192.168.0.112:5173\n";
    server.listen("0.0.0.0", 5173);

    // httplib::Server svr_static;

    // // Налаштування CORS
    // setupCORS(svr_static);

    // // Вказуємо MIME-типи
    // svr_static.set_file_extension_and_mimetype_mapping("js", "application/javascript");
    // svr_static.set_file_extension_and_mimetype_mapping("css", "text/css");
    // svr_static.set_file_extension_and_mimetype_mapping("html", "text/html");
    // svr_static.set_file_extension_and_mimetype_mapping("ico", "image/x-icon");
    // svr_static.set_file_extension_and_mimetype_mapping("svg", "image/svg+xml");

    // // Явна обробка vite.svg
    // svr_static.Get("/client/vite.svg", [](const httplib::Request &, httplib::Response &res) {
    //     std::ifstream file("/home/admin/Programs/Coliseum-project/client/dist/vite.svg", std::ios::binary);
    //     if (file) {
    //         std::cout << "Serving SVG file: ALL PATH - /client/dist/vite.svg" << std::endl;
    //         std::stringstream buffer;
    //         buffer << file.rdbuf();
    //         res.set_content(buffer.str(), "image/svg+xml");
    //     } else {
    //         std::cout << "Error: vite.svg not found at ALL PATH ../client/dist/vite.svg" << std::endl;
    //         res.status = 404;
    //         res.set_content("vite.svg not found", "text/plain");
    //     }
    // });

    // // Віддача статичних файлів з префіксом /client
    // svr_static.set_mount_point("/client", "../client/dist");

    // // Обробка SPA маршрутів
    // svr_static.set_error_handler([this](const httplib::Request &req, httplib::Response &res) {
    //     std::cout << "Static fallback for: " << req.path << std::endl;
    //     this->handleClientRoutes(req, res);
    // });

    // // Логування запитів
    // svr_static.set_pre_routing_handler([](const httplib::Request &req, httplib::Response &res) {
    //     std::cout << "Request: " << req.method << " " << req.path << " -> Status: " << res.status << std::endl;
    //     return httplib::Server::HandlerResponse::Unhandled;
    // });

    // std::cout << "Статичний сервер запущено на http://192.168.0.112:5173/content/\n";
    // svr_static.listen("0.0.0.0", 5173);
}

void Server::startApiServer() {
    httplib::Server svr_api;

    // Налаштування CORS
    setupCORS(svr_api);

    // API ендпоінти
    svr_api.Post("/login", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleAuthRequest(req, res, "/login");
    });

    svr_api.Post("/refreshtoken", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleRefreshTokenRequest(req, res);
    });

    svr_api.Post("/logout", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleLogoutRequest(req, res); // Виправлено shandle на handle
    });

    svr_api.Post("/logoutall", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleLogoutAllRequest(req, res);
    });

    // std::cout << "API сервер запущено на http://localhost:5182\n";
    svr_api.listen("localhost", 5182);
}