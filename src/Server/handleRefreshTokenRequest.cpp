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

    if (!reader.parse(req.body, data)) {
        Json::Value errorResponse;
        errorResponse["error"] = "Invalid JSON format";
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        res.set_header("Content-Type", "application/json");
        res.status = 400;
        res.set_content(errorResponseStr, "application/json");
        return;
    }

    std::string fingerPrint = data.get("fingerPrint", "default_fingerprint").asString();
    std::string email = data.get("email", "segor6052@gmail.com").asString();

    try {
        Accounts account;
        std::string refreshToken = account.generateRefreshToken(email, getKeyRefresh());

        if (refreshToken.empty()) {
            Json::Value errorResponse;
            errorResponse["error"] = "Failed to generate refresh token";
            Json::StreamWriterBuilder writer;
            std::string errorResponseStr = Json::writeString(writer, errorResponse);
            res.set_header("Content-Type", "application/json");
            res.status = 500;
            res.set_content(errorResponseStr, "application/json");
            return;
        }

        // 🔽 Відповідь лише з refreshToken
        Json::Value response;
        response["refreshToken"] = refreshToken;

        Json::StreamWriterBuilder writer;
        std::string responseStr = Json::writeString(writer, response);
        responseStr.erase(std::remove_if(responseStr.begin(), responseStr.end(),
            [](char c) { return c == '\xEF' || c == '\xBB' || c == '\xBF'; }), responseStr.end());

        res.set_header("Content-Type", "application/json");
        res.status = 200;
        res.set_content(responseStr, "application/json");

    } catch (const std::exception& e) {
        Json::Value errorResponse;
        errorResponse["error"] = std::string("Server error: ") + e.what();
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        res.set_header("Content-Type", "application/json");
        res.status = 500;
        res.set_content(errorResponseStr, "application/json");
    }
}
