#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

void Server::http_start() {
    httplib::Server svr;

    // Налаштування CORS
    setupCORS(svr);

    // Налаштування статичних файлів і MIME-типів
    setupStaticFiles(svr);

    // Ендпоінт для входу (/auth/login)
    svr.Post("/auth/login", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleAuthRequest(req, res, "/auth/login");
    });
    
    svr.Post("/login", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleAuthRequest(req, res, "/login");
    });
    
    svr.Post("/refreshtoken", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleRefreshTokenRequest(req, res);
    });
    
    svr.Post("/logout", [this](const httplib::Request &req, httplib::Response &res) {
        this->shandleLogoutRequest(req, res);
    });
    
    svr.Post("/logoutall", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleLogoutAllRequest(req, res);
    });
    
    svr.Get("/client/.*", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleClientRoutes(req, res);
    });
    
    svr.Get("/dashboard", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleClientRoutes(req, res);
    });
    
    svr.Get("/main", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleClientRoutes(req, res);
    });
    
    svr.Get("/auth", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleClientRoutes(req, res);
    });
    
    svr.Get("/", [this](const httplib::Request &req, httplib::Response &res) {
        this->handleClientRoutes(req, res);
    });

    std::cout << "Сервер запущено на http://localhost:5182/client\n";
    svr.listen("0.0.0.0", 5182);
}