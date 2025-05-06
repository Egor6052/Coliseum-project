#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

// Обробка JSON-запиту для автентифікації
void Server::handleAuthRequest(const httplib::Request &req, httplib::Response &res, const std::string &endpoint) {
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
            // Зберігаємо токени в БД
            std::string accessToken = account.generateAccessToken(email, getKeyAccess());
            std::string refreshToken = account.generateRefreshToken(email, getKeyRefresh());
            // Метод для збереження токенів в БД
            // account.storeTokens(email, accessToken, refreshToken);

            response["accessToken"] = accessToken;
            response["refreshToken"] = refreshToken;

            // response["accessToken"] = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOiJiM2ExZjE1ZS05ZDQyLTRjMWEtYTlmMi0wODNhZjEyMmY3MzMiLCJlbWFpbCI6InNlZ29yNjA1MkBnbWFpbC5jb20iLCJ1c2VyTmFtZSI6InNlZ29yIiwicm9sZXMiOiJbXCJ1c2VyXCJdIn0.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c";
            // response["refreshToken"] = "dGhpc2lzYXJlZnJlc2h0b2tlbg==";
            response["redirectUrl"] = "/";
            response["user"]["id"] = account.getUID();
            response["user"]["email"] = email;
            response["user"]["userName"] = account.getUserName(account.getUID());
            response["user"]["roles"] = account.getUserRole(account.getUID());

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