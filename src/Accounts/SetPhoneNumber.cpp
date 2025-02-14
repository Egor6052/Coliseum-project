#include "../../lib/Accounts.h"
#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <regex>
#include <stdexcept>

void Accounts::setPhoneNumber(std::string uid, std::string valuePhoneNumber) {
    std::regex phoneRegex(R"(^\+?\d{1,3}?[-.(]?\d{3}[-.)]?\d{3}[-.]?\d{2}[-.]?\d{2}$)");

    if (!std::regex_match(valuePhoneNumber, phoneRegex)) {
        throw std::invalid_argument("Invalid phone number format!");
    }

    // Оновлення телефону в базі даних
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
        }

        conn = mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0);
        if (!conn) {
            throw std::runtime_error("Failed to connect to MySQL database!");
        }

        // SQL-запит для оновлення номера телефону користувача за UID
        std::string updateQuery = "UPDATE " + getDBUsersName() + 
                            " SET phone_number = '" + valuePhoneNumber + 
                            "' WHERE uid = '" + uid + "'";

        if (mysql_query(conn, updateQuery.c_str())) {
            throw std::runtime_error("Failed to update phone number: " + std::string(mysql_error(conn)));
        }

        mysql_close(conn);

        // Зберігаємо новий номер телефону в об'єкті
        this->phoneNumber = valuePhoneNumber;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        throw;
    }
}

std::string Accounts::getUserPhoneNumber() {
    return this->phoneNumber;
}
