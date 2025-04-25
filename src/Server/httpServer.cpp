#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

// Функція для читання HTML-файлу
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        return "<h2>Error: Template file not found</h2>";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Функція для генерації спільного HTML-заголовка з навігацією
std::string getCommonHeader() {
    return R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Server Control Panel</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            background-color: #f4f4f4;
        }
        .navbar {
            background-color: #333;
            overflow: hidden;
        }
        .navbar a {
            float: left;
            display: block;
            color: white;
            text-align: center;
            padding: 14px 16px;
            text-decoration: none;
        }
        .navbar a:hover {
            background-color: #ddd;
            color: black;
        }
        .container {
            max-width: 800px;
            margin: 20px auto;
            padding: 20px;
            background: white;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        h2 {
            color: #555;
        }
        input, button, select {
            padding: 8px;
            margin: 5px 0;
            border: 1px solid #ccc;
            border-radius: 4px;
            width: 100%;
            box-sizing: border-box;
        }
        button {
            background-color: #28a745;
            color: white;
            border: none;
            cursor: pointer;
        }
        button:hover {
            background-color: #218838;
        }
        .response {
            margin-top: 10px;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            background-color: #f9f9f9;
            white-space: pre-wrap;
        }
    </style>
</head>
<body>
    <div class="navbar"></div>
    <div class="container">
)";
}

// Функція для генерації закриття HTML
std::string getCommonFooter() {
    return R"(
    </div>
</body>
</html>
)";
}

void Server::http_start() {
    // Ендпоінт для головної сторінки
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        std::string html = getCommonHeader();
        html += readFile("../templates/index.html");
        html += getCommonFooter();
        res.set_content(html, "text/html");
    });

    // Ендпоінт для команди (існуючий)
    svr.Post("/command", [this](const httplib::Request& req, httplib::Response& res) {
        http_server(req, res);
    });

    // Ендпоінт для реєстрації користувача (GET - сторінка, POST - логіка)
    svr.Get("/register", [](const httplib::Request& req, httplib::Response& res) {
        std::string html = getCommonHeader();
        html += readFile("../templates/register.html");
        html += getCommonFooter();
        res.set_content(html, "text/html");
    });

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
            account.registerNewUser(login, password, email, role);
            res.set_content("{\"status\":\"User registered successfully\"}", "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    // Ендпоінт для логіну (GET - сторінка, POST - логіка)
    svr.Get("/login", [](const httplib::Request& req, httplib::Response& res) {
        std::string html = getCommonHeader();
        html += readFile("../templates/login.html");
        html += getCommonFooter();
        res.set_content(html, "text/html");
    });

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

        if (account.Login(login, password)) {
            bool isAdmin = account.isAdministrator(login, password);
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

    // Ендпоінт для видалення запису (GET - сторінка, POST - логіка)
    svr.Get("/delete", [](const httplib::Request& req, httplib::Response& res) {
        std::string html = getCommonHeader();
        html += readFile("../templates/delete.html");
        html += getCommonFooter();
        res.set_content(html, "text/html");
    });

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

        if (!account.isAdministrator(login, password)) {
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

    // Ендпоінт для перегляду записів (GET - сторінка та логіка)
    svr.Get("/records", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("fetch")) {
            // Якщо є параметр fetch, повертаємо JSON
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
        } else {
            // Інакше повертаємо HTML-сторінку
            std::string html = getCommonHeader();
            html += readFile("../templates/records.html");
            html += getCommonFooter();
            res.set_content(html, "text/html");
        }
    });

    // Ендпоінт для створення бекапу (GET - сторінка, POST - логіка)
    svr.Get("/backup", [](const httplib::Request& req, httplib::Response& res) {
        std::string html = getCommonHeader();
        html += readFile("../templates/backup.html");
        html += getCommonFooter();
        res.set_content(html, "text/html");
    });

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

    // Ендпоінт для перегляду всіх користувачів (GET - сторінка та логіка)
    svr.Get("/users", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("login") && req.has_param("password")) {
            // Якщо є параметри login і password, повертаємо JSON
            std::string login = req.get_param_value("login");
            std::string password = req.get_param_value("password");

            if (!account.isAdministrator(login, password)) {
                res.status = 403;
                res.set_content("{\"error\":\"Access denied. Admin privileges required\"}", "application/json");
                return;
            }

            try {
                std::string users = account.getAllUsersFromDB();
                Json::Value response;
                response["status"] = "Success";
                response["users"] = users;

                Json::FastWriter writer;
                res.set_content(writer.write(response), "application/json");
            } catch (const std::exception& e) {
                res.status = 500;
                res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
            }
        } else {
            // Інакше повертаємо HTML-сторінку
            std::string html = getCommonHeader();
            html += readFile("../templates/users.html");
            html += getCommonFooter();
            res.set_content(html, "text/html");
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