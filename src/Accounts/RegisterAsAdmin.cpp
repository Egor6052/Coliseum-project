#include "../../lib/Accounts.h"
#include <string.h>
#include <iostream>
#include <mysql/mysql.h>

void Accounts::registerAsAdmin() {
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

    // Переключення на базу даних, яку ви хочете використовувати
    if (mysql_select_db(conn, getDBName().c_str())) {
        std::cerr << "Database selection failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    // Створення нового адміністратора для додатка
    std::string createUserQuery = "CREATE USER IF NOT EXISTS '" + getUserName() + "'@'localhost' IDENTIFIED BY '" + getUserPassword() + "';";

    if (mysql_query(conn, createUserQuery.c_str())) {
        std::cerr << "Admin creation failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    // Надання привілеїв адміністратора на конкретну базу даних
    std::string grantQuery = "GRANT ALL PRIVILEGES ON " + getDBName() + ".* TO '" + getUserName() + "'@'localhost';";

    if (mysql_query(conn, grantQuery.c_str())) {
        std::cerr << "Granting privileges failed: " << mysql_error(conn) << '\n';
        mysql_close(conn);
        return;
    }

    std::cout << "Admin registered successfully with full privileges.\n";
    mysql_close(conn);
}
