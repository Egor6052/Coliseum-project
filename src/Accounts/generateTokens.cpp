#include "../headers/Accounts.h"
#include <jwt-cpp/jwt.h>
#include <chrono>

std::string Accounts::generateAccessToken(const std::string &email, const std::string &secretKey) {
    // Секретний ключ для підпису токена
    // const std::string secretKey = ;

    // Генерація токена
    auto token = jwt::create()
        .set_issuer("ColiseumProject") // Видавець токена
        .set_subject(email)           // Email користувача
        .set_audience("http://localhost:5182") // Аудиторія
        .set_issued_at(std::chrono::system_clock::now()) // Час створення
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes(15))
        .sign(jwt::algorithm::hs256{secretKey}); // Підпис токена

    return token;
}

std::string Accounts::generateRefreshToken(const std::string &email, const std::string &secretKey) {
    // Секретний ключ для підпису токена
    // your_refresh_secret_key
    // const std::string secretKey = ;

    // Генерація токена
    auto token = jwt::create()
                    .set_issuer("ColiseumProject")
                    .set_subject(email)
                    .set_audience("http://localhost:5182")
                    .set_issued_at(std::chrono::system_clock::now())
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(24 * 7))                     // Refresh токен діє довше
                    .sign(jwt::algorithm::hs256{secretKey});

    return token;
}