#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Accounts.h"


bool Accounts::Login(const std::string& email, const std::string& password) {
    try {
        mysqlConnect();

        // Перевірка, чи існує користувач з таким email
        std::string checkQuery = "SELECT uid, login, password, email FROM " + getDBUsersName() + " WHERE email = '" + email + "'";
        if (mysql_query(conn, checkQuery.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        // Якщо користувача немає в базі
        if (mysql_num_rows(res) == 0) {
            std::cerr << "User not found.\n";
            logError("User not found.\n");
            mysqlDisconnection(res);
            return false;
        }

        // Перевірка пароля та отримання uid
        MYSQL_ROW row = mysql_fetch_row(res);
        std::string storedUid = row[0];
        std::string storedLogin = row[1];
        std::string storedPassword = row[2];
        std::string storedEmail = row[3];

        if (storedPassword != password) {
            std::cerr << "Incorrect password.\n";
            logError("Incorrect password.\n");
            mysqlDisconnection(res);
            return false;
        }

        this->Uid = storedUid;

        // Успішний логін, викликаємо методи з uid
        std::string userName = getUserName(storedUid);
        std::string userPassword = getUserPassword(storedUid);
        std::string userEmail = getUserEmail(storedUid);

        // Для перевірки виведемо отримані дані
        std::cout << "Logged in successfully!\n";
        std::cout << "UID: " << storedUid << "\n";
        std::cout << "Username: " << userName << "\n";
        std::cout << "Email: " << userEmail << "\n";

        mysqlDisconnection(res);

        return true;

    } catch (const std::exception &e) {
        std::string errorMessage = "Error: " + std::string(e.what()) + '\n';
        std::cerr << errorMessage;
        logError(errorMessage);
        mysqlDisconnection();
        return false;
    }
}