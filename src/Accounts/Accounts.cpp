#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Accounts.h"

Accounts::Accounts() {
    this->Uid = "";
    this->UserName = "";
    this->UserPassword = "";
    this->UserEmail = "";
}

Accounts::~Accounts() {
}

bool Accounts::isNotEmpty(const std::string& str) {
    return !str.empty();
}

void Accounts::setName(std::string valueName) {
    if (isNotEmpty(valueName)) {
        this->UserName = valueName;
    } else {
        std::cerr << "Error: User name cannot be empty!" << std::endl;
        logError("Error: User name cannot be empty!");
    }
}

void Accounts::setPassword(std::string valuePassword) {
    if (isNotEmpty(valuePassword)) {
        this->UserPassword = valuePassword;
    } else {
        std::cerr << "Error: Password cannot be empty!" << std::endl;
        logError("Error: Password cannot be empty!");
    }
}

void Accounts::setEmail(std::string valueEmail) {
    if (isNotEmpty(valueEmail)) {
        this->UserEmail = valueEmail;
    } else {
        std::cerr << "Error: Email cannot be empty!" << std::endl;
        logError("Error: Email cannot be empty!");
    }
}

std::string Accounts::getUserName(std::string uid) {
    try {
        mysqlConnect();

        std::string query = "SELECT login FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
        std::cout << "Executing query: " << query << std::endl;
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        std::string result = (row && row[0]) ? row[0] : "";
        std::cout << "Fetched username: " << result << std::endl;

        setName(result);

        mysqlDisconnection(res);
        return result;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError(e.what());
        mysqlDisconnection();
        return "";
    }
}

std::string Accounts::getUserPassword(std::string uid) {
    try {
        mysqlConnect();

        std::string query = "SELECT password FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        std::string result = (row && row[0]) ? row[0] : "";

        setPassword(result);

        mysqlDisconnection(res);
        return result;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError(e.what());
        mysqlDisconnection();
        return "";
    }
}

std::string Accounts::getUserEmail(std::string uid) {
    try {
        mysqlConnect();

        std::string query = "SELECT email FROM " + getDBUsersName() + " WHERE uid = '" + uid + "'";
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Failed to execute query: " + std::string(mysql_error(conn)));
            logError("Failed to execute query: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            throw std::runtime_error("Failed to store result: " + std::string(mysql_error(conn)));
            logError("Failed to store result: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        std::string result = (row && row[0]) ? row[0] : "";

        setEmail(result);

        mysqlDisconnection(res);
        return result;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError(e.what());
        mysqlDisconnection(nullptr);
        return "";
    }
}

std::string Accounts::getUID() {
    return Uid;
}

// bool Accounts::Login(std::string email, std::string password) {
//     try {
//         mysqlConnect();

//         // Логування назви таблиці
//         std::string tableName = getDBUsersName();
//         std::cout << "Table name: " << tableName << std::endl;

//         // Перевірка, чи існує користувач з таким email
//         std::string checkQuery = "SELECT uid, login, password, email FROM " + tableName + " WHERE email = '" + email + "'";
//         std::cout << "Executing query: " << checkQuery << std::endl;
//         if (mysql_query(conn, checkQuery.c_str())) {
//             std::string error = "Failed to execute query: " + std::string(mysql_error(conn));
//             std::cerr << error << std::endl;
//             logError(error);
//             throw std::runtime_error(error);
//         }

//         MYSQL_RES* res = mysql_store_result(conn);
//         if (!res) {
//             std::string error = "Failed to store result: " + std::string(mysql_error(conn));
//             std::cerr << error << std::endl;
//             logError(error);
//             throw std::runtime_error(error);
//         }

//         // Якщо користувача немає в базі
//         if (mysql_num_rows(res) == 0) {
//             std::cerr << "User not found for email: " << email << std::endl;
//             logError("User not found for email: " + email);
//             mysqlDisconnection(res);
//             return false;
//         }

//         // Перевірка пароля та отримання uid
//         MYSQL_ROW row = mysql_fetch_row(res);
//         std::string storedUid = row[0];
//         std::string storedLogin = row[1];
//         std::string storedPassword = row[2];
//         std::string storedEmail = row[3];

//         if (storedPassword != password) {
//             std::cerr << "Incorrect password for email: " << email << std::endl;
//             logError("Incorrect password for email: " + email);
//             mysqlDisconnection(res);
//             return false;
//         }

//         this->Uid = storedUid;

//         // Успішний логін, викликаємо методи з uid
//         std::string userName = getUserName(storedUid);
//         std::string userPassword = getUserPassword(storedUid);
//         std::string userEmail = getUserEmail(storedUid);

//         // Для перевірки виведемо отримані дані
//         std::cout << "Logged in successfully!\n";
//         std::cout << "UID: " << storedUid << "\n";
//         std::cout << "Username: " << userName << "\n";
//         std::cout << "Email: " << userEmail << "\n";

//         mysqlDisconnection(res);

//         return true;

//     } catch (const std::exception &e) {
//         std::string errorMessage = "Error in Login: " + std::string(e.what());
//         std::cerr << errorMessage << '\n';
//         logError(errorMessage);
//         mysqlDisconnection();
//         return false;
//     }
// }