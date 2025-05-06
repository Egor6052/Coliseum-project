
#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>


// Обробка запиту для оновлення токена
void Server::handleRefreshTokenRequest(const httplib::Request &req, httplib::Response &res) {
    std::cout << "Отримано POST-запит до /refreshtoken: " << req.body << std::endl;
    Json::Value json;
    Json::Reader reader;
    Json::Value data;

    if (reader.parse(req.body, data)) {
        std::string fingerPrint = data["fingerPrint"].asString();
        std::cout << "FingerPrint: " << fingerPrint << std::endl;

        // TODO, можна зробити: 
        // std::string accessToken = account.generateAccessToken(email, getKeyAccess());
        // std::string refreshToken = account.generateRefreshToken(email, getKeyRefresh());
        // // Метод для збереження токенів в БД
        // // account.storeTokens(email, accessToken, refreshToken);

        // response["accessToken"] = accessToken;
        // response["refreshToken"] = refreshToken;

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