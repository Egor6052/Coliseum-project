#include "../../lib/Accounts.h"
#include <string.h>
#include <iostream>
#include <mysql/mysql.h>

void Accounts::registerAsAdmin() {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
        }

        conn = mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0);
        if (!conn) {
            throw std::runtime_error("Failed to connect to MySQL database!");
        }

        // Перевірка, чи існує вже користувач з таким логіном
        std::string checkUserQuery = "SELECT * FROM " + getDBUsersName() + " WHERE login = '" + getUserName() + "' LIMIT 1";
        if (mysql_query(conn, checkUserQuery.c_str())) {
            throw std::runtime_error("Failed to check user existence: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0) {
            throw std::runtime_error("User with this login already exists!");
        }

        // Генерація UID
        std::string uid = generateUID();  // Викликаєте вашу функцію для генерації UID (якщо це рядок)

        // Якщо користувача не знайдено, вставляємо новий запис для адміністратора
        std::string insertUserQuery = "INSERT INTO " + getDBUsersName() + " (uid, login, password, role) VALUES ('" + uid + "', '" + getUserName() + "', '" + getUserPassword() + "', 'admin')";
        if (mysql_query(conn, insertUserQuery.c_str())) {
            throw std::runtime_error("Failed to insert user: " + std::string(mysql_error(conn)));
        }

        std::cout << "Admin registered successfully with login: " << getUserName() << " and UID: " << uid << std::endl;

        mysql_free_result(res);
        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

