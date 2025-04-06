#include <string.h>
#include <iostream>
#include "../../lib/mysql/mysql.h"
#include "../headers/Accounts.h"

void Accounts::registerNewUser(std::string login, std::string password, std::string email, std::string userRole) {
    try {
        mysqlConnect();

        // Перевірка, чи існує вже користувач з таким логіном
        std::string checkUserQuery = "SELECT * FROM " + getDBUsersName() + 
                                    " WHERE login = '" + login + "' LIMIT 1";

        if (mysql_query(conn, checkUserQuery.c_str())) {
            throw std::runtime_error("Failed to check user existence: " + std::string(mysql_error(conn)));
            logError("Failed to check user existence: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res && mysql_num_rows(res) > 0) {
            mysqlDisconnection(res);
            throw std::runtime_error(userRole + " with this login already exists!");
            logError(userRole + " with this login already exists!");
        }

        std::string uid = generateUID();

        // Вставка нового користувача
        std::string insertUserQuery = "INSERT INTO " + getDBUsersName() + 
                                    " (uid, login, password, email, role) VALUES ('" 
                                    + uid + "', '" 
                                    + login + "', '" 
                                    + password + "', '"
                                    + email + "', '"
                                    + userRole + "')";

        if (mysql_query(conn, insertUserQuery.c_str())) {
            throw std::runtime_error("Failed to insert " + userRole + ": " + std::string(mysql_error(conn)));
            logError("Failed to insert " + userRole + ": " + std::string(mysql_error(conn)));
        }

        // Фіксуємо транзакцію
        if (mysql_commit(conn)) {
            throw std::runtime_error("Failed to commit transaction: " + std::string(mysql_error(conn)));
            logError("Failed to commit transaction: " + std::string(mysql_error(conn)));
        }

        std::cout << userRole << " registered successfully: " 
                << "login: " << login
                << ", UID: " << uid 
                << ", Email: " << email << std::endl;

        mysqlDisconnection(res);

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + "\n";
        std::cerr << errorMessage;
        logError(errorMessage);
        // Якщо сталася помилка, відкатуємо транзакцію
        mysql_rollback(conn);
        mysqlDisconnection();
    }
}