#include <iostream>
#include <string>
#include "../../lib/mysql/mysql.h"
#include "../headers/Accounts.h"

Accounts::Accounts() { }

Accounts::~Accounts() { }


std::string Accounts::getUID(std::string email) {
    try {
        mysqlConnect();
        std::string useDBQuery = "USE " + getDBName() + ";";
        if (mysql_query(conn, useDBQuery.c_str())) {
            throw std::runtime_error("Failed to switch to database: " + std::string(mysql_error(conn)));
        }
        
        std::string query = "SELECT uid FROM " + getDBUsersName() + " WHERE login = '" + email + "'";
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
        Uid = (row && row[0]) ? row[0] : "";

        mysqlDisconnection(res);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        logError(e.what());
        mysqlDisconnection();
    }

    return Uid;
}