#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <mysql/mysql.h>
#include "../../lib/Database.h"

void Database::createBackup() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    try {
        conn = mysql_init(NULL);
        if (conn == NULL) {
            throw std::runtime_error("mysql_init() failed");
        }

        if (mysql_real_connect(conn, "localhost", getUserDBName().c_str(), getUserDBPassword().c_str(), getDBName().c_str(), 3306, NULL, 0) == NULL) {
            mysql_close(conn);
            throw std::runtime_error("mysql_real_connect() failed");
        }

        std::string query = "SELECT id, date, ip_address, sensor_name, current, voltage, active_power, reactive_power FROM " + getDBName() + " ORDER BY id ASC;";
        if (mysql_query(conn, query.c_str())) {
            mysql_close(conn);
            throw std::runtime_error("SELECT query failed");
        }

        res = mysql_store_result(conn);
        if (res == NULL) {
            mysql_close(conn);
            throw std::runtime_error("mysql_store_result() failed");
        }

        if (mysql_num_rows(res) == 0) {
            mysql_free_result(res);
            mysql_close(conn);
            throw std::runtime_error("No data found in the database to back up.");
        }

        // Directory for saving backups
        std::string backupDirectory = "../backups/";
        std::filesystem::create_directories(backupDirectory);

        // Name file
        std::string backupFileName = backupDirectory + getCurrentDateTime() + "_backup.csv";

        // Open file for writing
        std::ofstream backupFile(backupFileName);
        if (!backupFile.is_open()) {
            mysql_free_result(res);
            mysql_close(conn);
            throw std::runtime_error("Failed to open backup file for writing.");
        }

        // Writing data
        backupFile << "id,date,ip_address,sensor_name,current,voltage,active_power,reactive_power\n";

        while ((row = mysql_fetch_row(res)) != NULL) {
            backupFile << row[0] << ","
                    << row[1] << ","
                    << row[2] << ","
                    << row[3] << ","
                    << row[4] << ","
                    << row[5] << ","
                    << row[6] << ","
                    << row[7] << "\n";
        }

        backupFile.close();
        mysql_free_result(res);
        mysql_close(conn);
        std::cout << "\033[1m\033[35m˚｡⋆\033[36m Backup created successfully in file: \033[35m" << backupFileName << "\033[0m\n" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError creating backup: " << e.what() << "\033[0m\n";
    }
}
