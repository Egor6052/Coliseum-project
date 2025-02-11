#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include "../../lib/Database.h"

void Database::CreateTable() {
    try {
        MYSQL *conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed!");
        }

        conn = mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 0, nullptr, 0);
        if (!conn) {
            throw std::runtime_error("Failed to connect to MySQL database!");
        }

        // Створення таблиці, якщо вона не існує
        std::string createTableQuery = "CREATE TABLE IF NOT EXISTS " + getDBName() + " ("
                        "id INT AUTO_INCREMENT PRIMARY KEY, "
                        "date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                        "ip_address VARCHAR(255) NOT NULL, "
                        "sensor_name VARCHAR(255) NOT NULL, "
                        "current FLOAT NOT NULL, "
                        "voltage FLOAT NOT NULL, "
                        "active_power FLOAT NOT NULL, "
                        "reactive_power FLOAT NOT NULL"
                    ");";

        if (mysql_query(conn, createTableQuery.c_str())) {
            throw std::runtime_error("Failed to create table: " + std::string(mysql_error(conn)));
        }

        std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable '" + getDBName() + "' created successfully!\033[35m⊹₊⟡⋆\033[0m\n" << std::endl;

        mysql_close(conn);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}


