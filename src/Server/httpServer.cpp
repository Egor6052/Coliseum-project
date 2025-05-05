#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

namespace ServerUtils {

// Обробка JSON-запиту для автентифікації
void handleAuthRequest(const httplib::Request &req, httplib::Response &res, const std::string &endpoint) {
    std::cout << "Отримано POST-запит до " << endpoint << ": " << req.body << std::endl;
    Json::Value json;
    Json::Reader reader;
    Json::Value data;

    if (reader.parse(req.body, data)) {
        std::string email = data["email"].asString();
        std::string password = data["password"].asString();
        std::string fingerPrint = data["fingerPrint"].asString();
        std::cout << "Email: " << email << "\nPassword: " << password << "\nFingerPrint: " << fingerPrint << std::endl;

        // Перевірка логіна та пароля
        Accounts account;
        if (account.Login(email, password)) {
            // Формуємо успішну відповідь
            Json::Value response;
            response["accessToken"] = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOiJiM2ExZjE1ZS05ZDQyLTRjMWEtYTlmMi0wODNhZjEyMmY3MzMiLCJlbWFpbCI6InNlZ29yNjA1MkBnbWFpbC5jb20iLCJ1c2VyTmFtZSI6InNlZ29yIiwicm9sZXMiOiJbXCJ1c2VyXCJdIn0.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c";
            response["refreshToken"] = "dGhpc2lzYXJlZnJlc2h0b2tlbg==";
            response["redirectUrl"] = "/"; // Змінено на /
            response["user"]["id"] = "b3a1f15e-9d42-4c1a-a9f2-083af122f733";
            response["user"]["email"] = email;
            response["user"]["userName"] = "segor";
            response["user"]["roles"] = "[\"user\"]";

            Json::StreamWriterBuilder writer;
            std::string responseStr = Json::writeString(writer, response);
            std::cout << "Response: " << responseStr << std::endl;

            res.set_header("Authorization", "Bearer " + response["accessToken"].asString());
            res.set_content(responseStr, "application/json");
        } else {
            // Невдала авторизація
            Json::Value errorResponse;
            errorResponse["error"] = "Invalid email or password";
            Json::StreamWriterBuilder writer;
            std::string errorResponseStr = Json::writeString(writer, errorResponse);
            std::cout << "Error Response: " << errorResponseStr << std::endl;
            res.status = 401; // Unauthorized
            res.set_content(errorResponseStr, "application/json");
        }
    } else {
        Json::Value errorResponse;
        errorResponse["error"] = "Invalid JSON";
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.status = 400; // Bad Request
        res.set_content(errorResponseStr, "application/json");
    }
}

// Обробка запиту для оновлення токена
void handleRefreshTokenRequest(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано POST-запит до /refreshtoken: " << req.body << std::endl;
    Json::Value json;
    Json::Reader reader;
    Json::Value data;

    if (reader.parse(req.body, data)) {
        std::string fingerPrint = data["fingerPrint"].asString();
        std::cout << "FingerPrint: " << fingerPrint << std::endl;

        // Формуємо відповідь
        Json::Value response;
        response["accessToken"] = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOiJiM2ExZjE1ZS05ZDQyLTRjMWEtYTlmMi0wODNhZjEyMmY3MzMiLCJlbWFpbCI6InNlZ29yNjA1MkBnbWFpbC5jb20iLCJ1c2VyTmFtZSI6InNlZ29yIiwicm9sZXMiOiJbXCJ1c2VyXCJdIn0.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c";
        response["refreshToken"] = "dGhpc2lzYXJlZnJlc2h0b2tlbg==";

        Json::StreamWriterBuilder writer;
        std::string responseStr = Json::writeString(writer, response);
        std::cout << "Response: " << responseStr << std::endl;

        res.set_header("Authorization", "Bearer " + response["accessToken"].asString());
        res.set_content(responseStr, "application/json");
    } else {
        Json::Value errorResponse;
        errorResponse["error"] = "Invalid JSON";
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.status = 400; // Bad Request
        res.set_content(errorResponseStr, "application/json");
    }
}

// Обробка всіх клієнтських маршрутів (повернення index.html)
void handleClientRoutes(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано клієнтський запит: " << req.path << std::endl;
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

// Налаштування CORS
void setupCORS(httplib::Server &svr) {
    svr.set_pre_routing_handler([](const httplib::Request &req, httplib::Response &res) {
        std::cout << "Отримано запит: " << req.method << " " << req.path << std::endl;
        res.set_header("Access-Control-Allow-Origin", "http://localhost:5173");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
        res.set_header("Access-Control-Allow-Credentials", "true");

        if (req.method == "OPTIONS") {
            res.status = 200;
            return httplib::Server::HandlerResponse::Handled;
        }
        return httplib::Server::HandlerResponse::Unhandled;
    });
}

// Налаштування MIME-типів і статичних файлів
void setupStaticFiles(httplib::Server &svr) {
    svr.set_mount_point("/client", "../client/dist");

    svr.set_file_extension_and_mimetype_mapping("js", "text/javascript");
    svr.set_file_extension_and_mimetype_mapping("css", "text/css");
    svr.set_file_extension_and_mimetype_mapping("html", "text/html");
    svr.set_file_extension_and_mimetype_mapping("json", "application/json");
    svr.set_file_extension_and_mimetype_mapping("png", "image/png");
    svr.set_file_extension_and_mimetype_mapping("jpg", "image/jpeg");
    svr.set_file_extension_and_mimetype_mapping("svg", "image/svg+xml");
}

} // namespace ServerUtils

void Server::http_start() {
    httplib::Server svr;

    // Налаштування CORS
    ServerUtils::setupCORS(svr);

    // Налаштування статичних файлів і MIME-типів
    ServerUtils::setupStaticFiles(svr);

    // Ендпоінт для входу (/auth/login)
    svr.Post("/auth/login", [](const httplib::Request &req, httplib::Response &res) {
        ServerUtils::handleAuthRequest(req, res, "/auth/login");
    });

    // Ендпоінт для входу (/login)
    svr.Post("/login", [](const httplib::Request &req, httplib::Response &res) {
        ServerUtils::handleAuthRequest(req, res, "/login");
    });

    // Ендпоінт для оновлення токена (/refreshtoken)
    svr.Post("/refreshtoken", ServerUtils::handleRefreshTokenRequest);

    // Обробка всіх клієнтських маршрутів (SPA)
    svr.Get("/client/.*", ServerUtils::handleClientRoutes);
    svr.Get("/dashboard", ServerUtils::handleClientRoutes);
    svr.Get("/main", ServerUtils::handleClientRoutes);
    svr.Get("/auth", ServerUtils::handleClientRoutes);
    svr.Get("/", ServerUtils::handleClientRoutes);

    std::cout << "Сервер запущено на http://localhost:5182\n";
    svr.listen("0.0.0.0", 5182);
}