#include <iostream>
#include <fstream>
#include <algorithm>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

// Автентифікація в системі

void Server::handleAuthRequest(const httplib::Request &req, httplib::Response &res, const std::string &endpoint) {
    std::cout << "Отримано POST-запит до /login: " << req.body << std::endl;

    nlohmann::json data;

    try {
        // Парсинг JSON
        data = nlohmann::json::parse(req.body);
    } catch (const nlohmann::json::parse_error& e) {
        nlohmann::json errorResponse;
        errorResponse["error"] = "Invalid JSON format";
        std::string errorResponseStr = errorResponse.dump();
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.set_header("Content-Type", "application/json");
        res.status = 400;
        res.set_content(errorResponseStr, "application/json");
        return;
    }

    // Отримання полів із JSON
    std::string email = data.value("email", "");
    std::string password = data.value("password", "");
    std::string fingerPrint = data.value("fingerPrint", "");

    // Валідація вхідних даних
    if (email.empty() || password.empty()) {
        nlohmann::json errorResponse;
        errorResponse["error"] = "Email or password is missing";
        std::string errorResponseStr = errorResponse.dump();
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.set_header("Content-Type", "application/json");
        res.status = 400;
        res.set_content(errorResponseStr, "application/json");
        return;
    }

    try {
        Accounts account;
        if (!account.Login(email, password)) {
            nlohmann::json errorResponse;
            errorResponse["error"] = "Invalid credentials";
            std::string errorResponseStr = errorResponse.dump();
            std::cout << "Error Response: " << errorResponseStr << std::endl;
            res.set_header("Content-Type", "application/json");
            res.status = 401;
            res.set_content(errorResponseStr, "application/json");
            return;
        }

        // Генеруємо токени
        std::string accessToken = account.generateAccessToken(email, getKeyAccess());
        std::string refreshToken = account.generateRefreshToken(email, getKeyRefresh());
        std::cout << "Generated accessToken: " << accessToken << std::endl;
        std::cout << "Generated refreshToken: " << refreshToken << std::endl;

        // Перевірка токенів
        if (accessToken.empty()) {
            nlohmann::json errorResponse;
            errorResponse["error"] = "Failed to generate access token";
            std::string errorResponseStr = errorResponse.dump();
            std::cout << "Error Response: " << errorResponseStr << std::endl;
            res.set_header("Content-Type", "application/json");
            res.status = 500;
            res.set_content(errorResponseStr, "application/json");
            return;
        }

        // Відповідь із accessToken
        nlohmann::json response;
        response["accessToken"] = accessToken;
        // Додаємо refreshToken, якщо фронтенд може його обробити
        // response["refreshToken"] = refreshToken;

        std::string responseStr = response.dump();
        std::cout << "Response: " << responseStr << std::endl;

        res.set_header("Content-Type", "application/json");
        res.status = 200;
        res.set_content(responseStr, "application/json");

    } catch (const std::exception& e) {
        nlohmann::json errorResponse;
        errorResponse["error"] = std::string("Server error: ") + e.what();
        std::string errorResponseStr = errorResponse.dump();
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.set_header("Content-Type", "application/json");
        res.status = 500;
        res.set_content(errorResponseStr, "application/json");
    }
}