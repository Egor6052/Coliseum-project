#include "../../lib/Accounts.h"
#include <string.h>
#include <iostream>
#include <mysql/mysql.h>

std::string Accounts::getAllUsersFromDB() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string result;

    // Ініціалізація MySQL
    conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL initialization failed!\n";
        return "";
    }

    // Підключення як root
    if (!mysql_real_connect(conn, "localhost", "root", this->getAdminPassword().c_str(), nullptr, 0, nullptr, 0)) {
        std::cerr << "Connection failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return "";
    }

    // Запит для отримання всіх користувачів
    std::string query = "SELECT User, Host FROM mysql.user;";
    
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return "";
    }

    // Отримання результатів
    res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Error fetching results: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return "";
    }

    int num_fields = mysql_num_fields(res);
    if (num_fields == 0) {
        std::cerr << "No fields in the result\n";
    } else {
        std::cout << "Number of fields: " << num_fields << '\n';
    }

    // Формуємо рядок з користувачами
    while ((row = mysql_fetch_row(res)) != nullptr) {
        if (row[0] != nullptr && row[1] != nullptr) {
            result += "User: " + std::string(row[0]) + ", Host: " + std::string(row[1]) + "\n";
        } else {
            std::cerr << "Empty row encountered!\n";
        }
    }

    // Закриття з'єднання
    mysql_free_result(res);
    mysql_close(conn);

    return result;
}
