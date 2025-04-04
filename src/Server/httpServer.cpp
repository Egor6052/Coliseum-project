#include <iostream>
#include <thread>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

void Server::http_start() {
    // Ендпоінт для команди (існуючий)
    svr.Post("/command", [this](const httplib::Request& req, httplib::Response& res) {
        http_server(req, res);
    });

    // Ендпоінт для реєстрації користувача
    svr.Post("/register", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.method != "POST") {
            res.status = 405;
            res.set_content("{\"error\":\"Method Not Allowed\"}", "application/json");
            return;
        }

        Json::Value jsonData;
        Json::Reader reader;
        if (!reader.parse(req.body, jsonData) ||
            !jsonData.isMember("login") ||
            !jsonData.isMember("password") ||
            !jsonData.isMember("email") ||
            !jsonData.isMember("role")) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON or missing fields (login, password, email, role)\"}", "application/json");
            return;
        }

        std::string login = jsonData["login"].asString();
        std::string password = jsonData["password"].asString();
        std::string email = jsonData["email"].asString();
        std::string role = jsonData["role"].asString();

        if (role != "user" && role != "admin") {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid role. Must be 'user' or 'admin'\"}", "application/json");
            return;
        }

        try {
            registerNewUser(login, password, email, role);
            res.set_content("{\"status\":\"User registered successfully\"}", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    // Ендпоінт для логіну
    svr.Post("/login", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.method != "POST") {
            res.status = 405;
            res.set_content("{\"error\":\"Method Not Allowed\"}", "application/json");
            return;
        }

        Json::Value jsonData;
        Json::Reader reader;
        if (!reader.parse(req.body, jsonData) ||
            !jsonData.isMember("login") ||
            !jsonData.isMember("password")) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON or missing fields (login, password)\"}", "application/json");
            return;
        }

        std::string login = jsonData["login"].asString();
        std::string password = jsonData["password"].asString();

        if (Login(login, password)) {
            bool isAdmin = isAdministrator(login, password);
            Json::Value response;
            response["status"] = "Login successful";
            response["user"] = login;
            response["isAdmin"] = isAdmin;

            Json::FastWriter writer;
            res.set_content(writer.write(response), "application/json");
        } else {
            res.status = 401;
            res.set_content("{\"error\":\"Login failed. Check your credentials\"}", "application/json");
        }
    });

    // Ендпоінт для видалення запису (тільки для адмінів)
    svr.Post("/delete", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.method != "POST") {
            res.status = 405;
            res.set_content("{\"error\":\"Method Not Allowed\"}", "application/json");
            return;
        }

        Json::Value jsonData;
        Json::Reader reader;
        if (!reader.parse(req.body, jsonData) ||
            !jsonData.isMember("id") ||
            !jsonData.isMember("login") ||
            !jsonData.isMember("password")) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON or missing fields (id, login, password)\"}", "application/json");
            return;
        }

        std::string id = jsonData["id"].asString();
        std::string login = jsonData["login"].asString();
        std::string password = jsonData["password"].asString();

        if (!isAdministrator(login, password)) {
            res.status = 403;
            res.set_content("{\"error\":\"Access denied. Admin privileges required\"}", "application/json");
            return;
        }

        try {
            deleteData(id);
            res.set_content("{\"status\":\"Record deleted successfully\"}", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    // Ендпоінт для перегляду записів
    svr.Get("/records", [this](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string data = getData();
            Json::Value response;
            response["status"] = "Success";
            response["data"] = data;

            Json::FastWriter writer;
            res.set_content(writer.write(response), "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    // Ендпоінт для створення бекапу
    svr.Post("/backup", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.method != "POST") {
            res.status = 405;
            res.set_content("{\"error\":\"Method Not Allowed\"}", "application/json");
            return;
        }

        try {
            createBackup();
            res.set_content("{\"status\":\"Backup created successfully\"}", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    // Ендпоінт для перегляду всіх користувачів (тільки для адмінів)
    svr.Get("/users", [this](const httplib::Request& req, httplib::Response& res) {
        if (!req.has_param("login") || !req.has_param("password")) {
            res.status = 400;
            res.set_content("{\"error\":\"Missing query parameters (login, password)\"}", "application/json");
            return;
        }

        std::string login = req.get_param_value("login");
        std::string password = req.get_param_value("password");

        if (!isAdministrator(login, password)) {
            res.status = 403;
            res.set_content("{\"error\":\"Access denied. Admin privileges required\"}", "application/json");
            return;
        }

        try {
            std::string users = getAllUsersFromDB();
            Json::Value response;
            response["status"] = "Success";
            response["users"] = users;

            Json::FastWriter writer;
            res.set_content(writer.write(response), "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    // Запуск сервера в окремому потоці
    std::thread server_thread([this]() {
        svr.listen("0.0.0.0", 8080);
    });

    server_thread.detach();
}

void Server::http_server(const httplib::Request& req, httplib::Response& res) {
    if (req.method != "POST") {
        res.status = 405;
        res.set_content("{\"error\":\"Method Not Allowed\"}", "application/json");
        return;
    }

    Json::Value jsonData;
    Json::Reader reader;
    if (!reader.parse(req.body, jsonData) || !jsonData.isMember("command") || !jsonData.isMember("value")) {
        res.status = 400;
        res.set_content("{\"error\":\"Invalid JSON or missing fields\"}", "application/json");
        return;
    }

    std::string command = jsonData["command"].asString();
    int value = jsonData["value"].asInt();

    std::cout << getLoggerDateTime() << " | Command: " << command << ", Value: " << value << " | ";

    if (command == "start") {
        std::cout << "START action executed" << std::endl;
    } else if (command == "stop") {
        std::cout << "STOP action executed" << std::endl;
    } else {
        res.status = 400;
        res.set_content("{\"error\":\"Unknown command\"}", "application/json");
        return;
    }

    res.set_content("{\"status\":\"OK\"}", "application/json");
}