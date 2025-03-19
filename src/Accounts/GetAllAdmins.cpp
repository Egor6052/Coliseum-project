#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <nlohmann/json.hpp>
#include "../headers/Database.h"


std::string Accounts::getAllAdminsFromDB() {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
            logError("MySQL initialization failed!");
        }

        conn = mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0);
        if (!conn) {
            throw std::runtime_error("Failed to connect to MySQL database!");
            logError("Failed to connect to MySQL database!");
        }

        // Запит для отримання всіх адміністраторів
        std::string query = "SELECT uid, login, email, phone_number, role FROM " + getDBUsersName() + " WHERE role = 'admin'";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        // Обробка результату запиту
        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        nlohmann::json adminsJson = nlohmann::json::array();
        int adminCount = 0;

        // Логування для перевірки кількості рядків
        std::cout << "Total number of rows: " << mysql_num_rows(res) << std::endl;

        // Формуємо в JSON форматі
        while ((row = mysql_fetch_row(res))) {
            if (row[0] && row[1] && row[2] && row[3] && row[4]) {
                nlohmann::json admin = {
                    {"uid", row[0]},
                    {"login", row[1]},
                    {"email", row[2]},
                    {"phone_number", row[3]},
                    {"role", row[4]}
                };
                adminsJson.push_back(admin);
                adminCount++;
            }
        }

        mysql_free_result(res);
        mysql_close(conn);

        // Формуємо результат з кількістю адміністраторів
        nlohmann::json result = {
            {"admins", adminsJson},
            {"total_admins", adminCount}
        };

        return result.dump(4);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        nlohmann::json errorResponse = {{"error", e.what()}};
        logError(errorResponse);
        return errorResponse.dump(4);
    }
}

