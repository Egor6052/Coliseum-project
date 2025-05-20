#include <iostream>
#include <string>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

void Server::handleRefreshTokenRequest(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано POST-запит до /refreshtoken: " << req.body << std::endl;

    Json::Value data;
    Json::Reader reader;

    // Перевірка парсингу JSON
    if (!reader.parse(req.body, data)) {
        Json::Value errorResponse;
        errorResponse["error"] = "Invalid JSON format";
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.set_header("Content-Type", "application/json");
        res.status = 400;
        res.set_content(errorResponseStr, "application/json");
        return;
    }

    // Отримуємо fingerPrint (якщо відсутній, використовуємо заглушку)
    std::string fingerPrint = data.get("fingerPrint", "default_fingerprint").asString();
    std::cout << "FingerPrint: " << fingerPrint << std::endl;

    try {
        // Отримуємо email
        std::string email = data.get("email", "segor6052@gmail.com").asString();
        std::cout << "Email: " << email << std::endl;

        // Генерація токенів
        Accounts account;
        std::string accessToken = account.generateAccessToken(email, getKeyAccess());
        std::string refreshToken = account.generateRefreshToken(email, getKeyRefresh());
        std::cout << "Generated accessToken: " << accessToken << std::endl;
        std::cout << "Generated refreshToken: " << refreshToken << std::endl;

        // Перевірка токенів
        if (accessToken.empty() || refreshToken.empty()) {
            Json::Value errorResponse;
            errorResponse["error"] = "Failed to generate tokens";
            Json::StreamWriterBuilder writer;
            std::string errorResponseStr = Json::writeString(writer, errorResponse);
            std::cout << "Error Response: " << errorResponseStr << std::endl;
            res.set_header("Content-Type", "application/json");
            res.status = 500;
            res.set_content(errorResponseStr, "application/json");
            return;
        }

        // Формуємо відповідь
        Json::Value response;
        response["accessToken"] = accessToken;
        response["refreshToken"] = refreshToken;

        Json::StreamWriterBuilder writer;
        std::string responseStr = Json::writeString(writer, response);
        // Видаляємо BOM-символи
        responseStr.erase(std::remove_if(responseStr.begin(), responseStr.end(),
            [](char c) { return c == '\xEF' || c == '\xBB' || c == '\xBF'; }), responseStr.end());
        std::cout << "Response: " << responseStr << std::endl;

        res.set_header("Content-Type", "application/json");
        res.status = 200;
        res.set_content(responseStr, "application/json");
    } catch (const std::exception& e) {
        Json::Value errorResponse;
        errorResponse["error"] = std::string("Server error: ") + e.what();
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.set_header("Content-Type", "application/json");
        res.status = 500;
        res.set_content(errorResponseStr, "application/json");
    }
}