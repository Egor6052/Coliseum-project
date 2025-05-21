#include <iostream>
#include <fstream>
#include <algorithm>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

void Server::handleAuthRequest(const httplib::Request &req, httplib::Response &res, const std::string &endpoint) {
    std::cout << "Отримано POST-запит до /login: " << req.body << std::endl;

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

    std::string email = data.get("email", "").asString();
    std::string password = data.get("password", "").asString();
    std::string fingerPrint = data.get("fingerPrint", "").asString();

    // Валідація вхідних даних
    if (email.empty() || password.empty()) {
        Json::Value errorResponse;
        errorResponse["error"] = "Email or password is missing";
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.set_header("Content-Type", "application/json");
        res.status = 400;
        res.set_content(errorResponseStr, "application/json");
        return;
    }

    try {
        Accounts account;
        if (!account.Login(email, password)) {
            Json::Value errorResponse;
            errorResponse["error"] = "Invalid credentials";
            Json::StreamWriterBuilder writer;
            std::string errorResponseStr = Json::writeString(writer, errorResponse);
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
        if (refreshToken.empty()) {
            Json::Value errorResponse;
            errorResponse["error"] = "Failed to generate refresh token";
            Json::StreamWriterBuilder writer;
            std::string errorResponseStr = Json::writeString(writer, errorResponse);
            std::cout << "Error Response: " << errorResponseStr << std::endl;
            res.set_header("Content-Type", "application/json");
            res.status = 500;
            res.set_content(errorResponseStr, "application/json");
            return;
        }

        // Відповідь: тільки refreshToken як plain text
        std::string responseStr = refreshToken;
        std::cout << "Response (refreshToken only): " << responseStr << std::endl;

        res.set_header("Content-Type", "text/plain");
        res.status = 200;
        res.set_content(responseStr, "text/plain");
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
