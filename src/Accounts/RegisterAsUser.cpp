#include "../../lib/Accounts.h"
#include <string.h>
#include <iostream>
#include <mysql/mysql.h>


void Accounts::registerAsUser() {
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

    // Створення нового користувача для додатка з мінімальними правами
    std::string createUserQuery = "CREATE USER IF NOT EXISTS '" + getUserName() + "'@'localhost' IDENTIFIED BY '" + getUserPassword() + "';";

    if (mysql_query(conn, createUserQuery.c_str())) {
        std::cerr << "User creation failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    // Надання прав лише для перегляду (SELECT)
    std::string grantQuery = "GRANT SELECT ON " + getDBName() + ".* TO '" + getUserName() + "'@'localhost';";

    if (mysql_query(conn, grantQuery.c_str())) {
        std::cerr << "Granting privileges failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    std::cout << "User registered successfully with SELECT privileges.\n";
    mysql_close(conn);
}
