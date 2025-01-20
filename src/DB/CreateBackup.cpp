#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include <fstream>
#include "../../lib/Database.h"


void Database::createBackup() {
    try {
        pqxx::connection conn("dbname=sensordata user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT id, date, ip_address, sensor_name, current, voltage, active_power, reactive_power FROM public.sensordata ORDER BY id ASC;");

        if (res.empty()) {
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
            throw std::runtime_error("Failed to open backup file for writing.");
        }

        // Writing data
        backupFile << "id,date,ip_address,sensor_name,current,voltage,active_power,reactive_power\n";

        for (const auto& row : res) {
            backupFile 
                << row["id"].as<std::string>() << ","
                << row["date"].as<std::string>() << ","
                << row["ip_address"].as<std::string>() << ","
                << row["sensor_name"].as<std::string>() << ","
                << row["current"].as<float>() << ","
                << row["voltage"].as<float>() << ","
                << row["active_power"].as<float>() << ","
                << row["reactive_power"].as<float>() << "\n";
        }

        backupFile.close();
        std::cout << "\033[1m\033[35m˚｡⋆\033[36m Backup created successfully in file: \033[35m" << backupFileName << "\033[0m\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\033[31mError creating backup: " << e.what() << "\033[0m\n";
    }
}

