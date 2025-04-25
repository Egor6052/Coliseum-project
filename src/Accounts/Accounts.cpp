// #include "../headers/Accounts.h"
#include "../headers/Accounts.h"
#include <string.h>
#include <iostream>

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