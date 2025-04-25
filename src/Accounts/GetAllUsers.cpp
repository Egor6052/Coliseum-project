#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"

#include <nlohmann/json.hpp>
#include "../headers/Accounts.h"


std::string Accounts::getAllUsersFromDB()
{
    try
    {
        mysqlConnect();

        // Запит для отримання всіх користувачів
        std::string query = "SELECT uid, login, email, role FROM " + getDBUsersName();

        if (mysql_query(conn, query.c_str()))
        {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        // Обробка результату запиту
        MYSQL_RES *res = mysql_store_result(conn);
        if (!res)
        {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        nlohmann::json usersJson = nlohmann::json::array();
        int usersCount = 0;

        // Формуємо в JSON форматі
        while ((row = mysql_fetch_row(res)))
        {
            if (row[0] && row[1] && row[2] && row[3])
            {
                nlohmann::json user = {
                    {"uid", row[0]},
                    {"login", row[1]},
                    {"email", row[2]},
                    {"role", row[3]}};
                usersJson.push_back(user);
                usersCount++;
            }
        }

        mysqlDisconnection(res);

        // Формуємо результат з кількістю користувачів
        nlohmann::json result = {
            {"users", usersJson},
            {"total_users", usersCount}};

        return result.dump(4);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        nlohmann::json errorResponse = {{"error", e.what()}};
        logError(errorResponse);
        mysqlDisconnection();
        return errorResponse.dump(4);
    }
}