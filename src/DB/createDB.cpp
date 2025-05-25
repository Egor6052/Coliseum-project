#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Database.h"


void Database::createDB() {
    try {
        mysqlConnect();

        // SQL-запит для створення бази даних, якщо не існує
        std::string createDBQuery = "CREATE DATABASE IF NOT EXISTS " + getDBName() + ";";

        if (mysql_query(conn, createDBQuery.c_str())) {
            std::string err = mysql_error(conn);
            std::cerr << "Failed to create database: " << err << std::endl;
            logError("Failed to create database: " + err);
            throw std::runtime_error("MySQL Error: " + err);
        }

        std::cout << "\033[1m\033[32m✓ Базу даних '" << getDBName() << "' створено або вже існує.\033[0m\n";

        // Переключення на створену базу даних
        std::string useDBQuery = "USE " + getDBName() + ";";
        if (mysql_query(conn, useDBQuery.c_str())) {
            std::string err = mysql_error(conn);
            std::cerr << "Failed to switch to database: " << err << std::endl;
            logError("Failed to switch to database: " + err);
            throw std::runtime_error("MySQL Error: " + err);
        }

        mysqlDisconnection();
    } catch (const std::exception &e) {
        std::cerr << "Exception in createDB: " << e.what() << std::endl;
        logError("Exception in createDB: " + std::string(e.what()));
        mysqlDisconnection();
    }
}
