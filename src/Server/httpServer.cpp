#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
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
        handleAuthRequest(req, res, "/auth/login");
    });
    
    svr.Post("/login", [this](const httplib::Request &req, httplib::Response &res) {
        handleAuthRequest(req, res, "/login");
    });
    
    svr.Post("/refreshtoken", [this](const httplib::Request &req, httplib::Response &res) {
        handleRefreshTokenRequest(req, res);
    });
    
    svr.Post("/logout", [this](const httplib::Request &req, httplib::Response &res) {
        handleLogoutRequest(req, res);
    });
    
    svr.Post("/logoutall", [this](const httplib::Request &req, httplib::Response &res) {
        handleLogoutAllRequest(req, res);
    });
    
    svr.Get("/client/.*", [this](const httplib::Request &req, httplib::Response &res) {
        handleClientRoutes(req, res);
    });
    
    svr.Get("/dashboard", [this](const httplib::Request &req, httplib::Response &res) {
        handleClientRoutes(req, res);
    });
    
    svr.Get("/main", [this](const httplib::Request &req, httplib::Response &res) {
        handleClientRoutes(req, res);
    });
    
    svr.Get("/auth", [this](const httplib::Request &req, httplib::Response &res) {
        handleClientRoutes(req, res);
    });
    
    svr.Get("/", [this](const httplib::Request &req, httplib::Response &res) {
        handleClientRoutes(req, res);
    });
    
    // Ендпоінт для виходу з усіх сесій (/logoutall)
    svr.Post("/logoutall", handleLogoutAllRequest);

    // Обробка всіх клієнтських маршрутів (SPA)
    svr.Get("/client/.*", handleClientRoutes);
    svr.Get("/dashboard", handleClientRoutes);
    svr.Get("/main", handleClientRoutes);
    svr.Get("/auth", handleClientRoutes);
    svr.Get("/", handleClientRoutes);

    std::cout << "Сервер запущено на http://localhost:5182\n";
    svr.listen("0.0.0.0", 5182);
}