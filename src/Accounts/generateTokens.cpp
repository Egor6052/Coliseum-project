#include "../headers/Accounts.h"
#include <jwt-cpp/jwt.h>
// #include "lib/jwt-cpp/include/jwt-cpp/jwt.h"
#include <chrono>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>


std::string Accounts::generateAccessToken(const std::string& email, const std::string& secretKey, const std::string& fingerPrint) {
    try {
        // Перевірка, чи є Uid після логіну
        if (Uid.empty()) {
            std::cerr << "No user logged in for access token generation" << std::endl;
            logError("No user logged in for access token generation");
            return "";
        }

        // Отримання даних користувача
        std::string userDataJson = getUserData(Uid);
        nlohmann::json userData;
        try {
            userData = nlohmann::json::parse(userDataJson);
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Failed to parse user data JSON: " << e.what() << std::endl;
            logError("Failed to parse user data JSON: " + std::string(e.what()));
            return "";
        }

        // Перевірка на помилку в userData
        if (userData.contains("error")) {
            std::cerr << "Error in user data: " << userData["error"] << std::endl;
            logError("Error in user data: " + userData["error"].get<std::string>());
            return "";
        }

        std::string userId = userData.contains("uid") ? userData["uid"].get<std::string>() : "";
        std::string userName = userData.contains("name") ? userData["name"].get<std::string>() : "";
        std::string userEmail = userData.contains("email") ? userData["email"].get<std::string>() : "";
        std::string role = userData.contains("role") ? userData["role"].get<std::string>() : "";

        // Перетворення ролі в масив для фронтенду
        std::vector<std::string> roles;
        if (!role.empty()) {
            roles.push_back(role);
        }
        nlohmann::json rolesJson = roles;
        std::string rolesString = rolesJson.dump(); // Наприклад, ["user"] або []

        // Генерація токена
        auto token = jwt::create()
            .set_issuer("ColiseumProject")
            .set_subject(email)
            .set_audience("client")
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes(15))
            .set_payload_claim("userId", jwt::claim(userId))
            .set_payload_claim("userName", jwt::claim(userName))
            .set_payload_claim("roles", jwt::claim(rolesString))
            .set_payload_claim("fingerPrint", jwt::claim(fingerPrint))
            .sign(jwt::algorithm::hs256{secretKey});

        return token;
    } catch (const std::exception& e) {
        std::cerr << "Error generating access token: " << e.what() << std::endl;
        logError("Error generating access token: " + std::string(e.what()));
        return "";
    }
}

std::string Accounts::generateRefreshToken(const std::string& email, const std::string& secretKey, const std::string& fingerPrint) {
    try {
        // Генерація refresh токена
        auto token = jwt::create()
            .set_issuer("ColiseumProject")
            .set_subject(email)
            .set_audience("client")
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(24 * 7))
            .set_payload_claim("fingerPrint", jwt::claim(fingerPrint))
            .sign(jwt::algorithm::hs256{secretKey});

        return token;
    } catch (const std::exception& e) {
        std::cerr << "Error generating refresh token: " << e.what() << std::endl;
        logError("Error generating refresh token: " + std::string(e.what()));
        return "";
    }
}