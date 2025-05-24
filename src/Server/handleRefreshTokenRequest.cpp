#include <iostream>
#include <string>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

void Server::handleRefreshTokenRequest(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано POST-запит до /refreshtoken: " << req.body << std::endl;

    nlohmann::json data;

    try {
        // Парсинг JSON
        data = nlohmann::json::parse(req.body);
    } catch (const nlohmann::json::parse_error& e) {
        nlohmann::json errorResponse;
        errorResponse["error"] = "Invalid JSON format";
        std::string errorResponseStr = errorResponse.dump();
        res.set_header("Content-Type", "application/json");
        res.status = 400;
        res.set_content(errorResponseStr, "application/json");
        return;
    }

    // Отримання полів із JSON
    std::string fingerPrint = data.value("fingerPrint", "default_fingerprint");

    try {
        Accounts account;
        // Припускаємо, що generateAccessToken може отримати email із контексту fingerPrint
        // Потрібно реалізувати логіку в Accounts::generateAccessToken
        std::string accessToken = account.generateAccessToken("", getKeyAccess(), fingerPrint);
        std::string refreshToken = account.generateRefreshToken("", getKeyRefresh(), fingerPrint);

        if (accessToken.empty()) {
            nlohmann::json errorResponse;
            errorResponse["error"] = "Failed to generate access token";
            std::string errorResponseStr = errorResponse.dump();
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
        res.set_header("Content-Type", "application/json");
        res.status = 500;
        res.set_content(errorResponseStr, "application/json");
    }
}