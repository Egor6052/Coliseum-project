#include "../../lib/Accounts.h"
#include <string.h>
#include <iostream>
#include <mysql/mysql.h>

void Accounts::registerUser() {
    MYSQL *conn;
    conn = mysql_init(nullptr);

    if (!conn) {
        std::cerr << "MySQL initialization failed!\n";
        return;
    }

    // Підключення як root
    if (!mysql_real_connect(conn, "localhost", "root", this->getAdminPassword().c_str(), nullptr, 0, nullptr, 0)) {
        std::cerr << "Connection failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    // Отримуємо дані для створення нового користувача
    // std::string username = getUserName();
    // std::string password = getUserPassword();
    // std::string uid = getUID();

    // Створення нового користувача для додатка
    std::string createUserQuery = "CREATE USER IF NOT EXISTS '" + getUserName() + "'@'localhost' IDENTIFIED BY '" + getUserPassword() + "';";
    
    if (mysql_query(conn, createUserQuery.c_str())) {
        std::cerr << "User creation failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    // Надання привілеїв для користувача (мінімальні права - лише SELECT)
    std::string grantQuery = "GRANT SELECT ON " + getDBName() + ".* TO '" + getUserName() + "'@'localhost';";
    
    if (mysql_query(conn, grantQuery.c_str())) {
        std::cerr << "Granting privileges failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    std::cout << "User registered successfully with SELECT privileges.\n";
    mysql_close(conn);
}

