#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Database.h"

void Database::CreateTable() {
    try {
        mysqlConnect();

        // Створення таблиці для користувачів
        std::string createUsersTableQuery = "CREATE TABLE IF NOT EXISTS " + getDBUsersName() + " ("
            "uid VARCHAR(255) PRIMARY KEY, "
            "login VARCHAR(255) NOT NULL UNIQUE, "
            "password VARCHAR(255) NOT NULL, "
            "email VARCHAR(255) NULL, "
            "role ENUM('user', 'admin') NOT NULL DEFAULT 'user'"
        ");";

        if (mysql_query(conn, createUsersTableQuery.c_str())) {
            std::cout << "Failed to create " + getDBUsersName() + " table: " + std::string(mysql_error(conn)) << std::endl;
            throw std::runtime_error("Failed to create " + getDBUsersName() + " table: " + std::string(mysql_error(conn)));
            logError("Failed to create " + getDBUsersName() + " table: " + std::string(mysql_error(conn)));
        }

        std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable " + getDBUsersName() + " created successfully!\033[35m⊹₊⟡⋆\033[0m\n";

        // Створення таблиці для показників датчиків
        std::string createSensorDataTableQuery = "CREATE TABLE IF NOT EXISTS " + getDBName() + " ("
            "id INT AUTO_INCREMENT PRIMARY KEY, "
            "date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
            "ip_address VARCHAR(255) NOT NULL, "
            "sensor_name VARCHAR(255) NOT NULL, "
            "current FLOAT NOT NULL, "
            "voltage FLOAT NOT NULL, "
            "active_power FLOAT NOT NULL, "
            "reactive_power FLOAT NOT NULL"
        ");";

        if (mysql_query(conn, createSensorDataTableQuery.c_str())) {
            throw std::runtime_error("Failed to create " + getDBName() + " table: " + std::string(mysql_error(conn)));
            logError("Failed to create " + getDBName() + " table: " + std::string(mysql_error(conn)));
        }

        std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable " + getDBName() + " created successfully!\033[35m⊹₊⟡⋆\033[0m\n" << std::endl;

        mysqlDisconnection();

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + "\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
    }

    std::cout << "\033[1m\033[35m˚｡⋆\033[36mDatabase created successfully!\033[35m⋆｡˚\033[0m\n" << std::endl;
}