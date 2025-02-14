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
        std::string checkUserQuery = "SELECT * FROM " + getDBUsersName() + 
                                    " WHERE login = '" + getUserName() + "' LIMIT 1";

        if (mysql_query(conn, checkUserQuery.c_str())) {
            throw std::runtime_error("Failed to check admin existence: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res && mysql_num_rows(res) > 0) {
            mysql_free_result(res);
            throw std::runtime_error("Admin with this login, already exists!");
        }

        std::string uid = generateUID();
        // для об'єкта
        setUID();

        // Вставка нового користувача
        std::string insertUserQuery = "INSERT INTO " + getDBUsersName() + 
                            " (uid, login, password, email, phone_number, role) VALUES ('" 
                            + uid + "', '" 
                            + getUserName() + "', '" 
                            + getUserPassword() + "', " 
                            + (getUserEmail().empty() ? "NULL" : "'" + getUserEmail() + "'") + ", " 
                            + (getUserPhoneNumber().empty() ? "NULL" : "'" + getUserPhoneNumber() + "'") + ", 'admin')";


        if (mysql_query(conn, insertUserQuery.c_str())) {
            throw std::runtime_error("Failed to insert admin: " + std::string(mysql_error(conn)));
        }

        std::cout << "Admin registered successfully with login: " << getUserName() 
                << ", \nUID: " << uid 
                << ", \nEmail: " << getUserEmail() 
                << ", \nPhone: " << getUserPhoneNumber() << std::endl;

        mysql_free_result(res);
        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

