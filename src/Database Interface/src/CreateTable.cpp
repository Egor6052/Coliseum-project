#include <pqxx/pqxx> 
#include "../lib/User.h"

void User::CreateTable(std::string valueAnswer){
        if (!valueAnswer.empty() && valueAnswer.length() <= 50) {

        // Підключення до бази даних
        pqxx::connection conn("dbname=server user=" + getUserName() + " password="+ getUserPassword() + " host= " + getHostName() + "");
        if (conn.is_open()) {
            std::cout << "Connected to database successfully: " << conn.dbname() << std::endl;
        } else {
            std::cerr << "Failed to connect to database!" << std::endl;
            return;
        }

        // Виконання SQL-запитів
        pqxx::work txn(conn);

        // Створення таблиці
        try {
            std::string tableName;

            printf("Enter the TABLE name: ");
            std::getline(std::cin, tableName);

            if (tableName.empty()) {
                throw std::invalid_argument("Table name cannot be empty!");
            } else {
                txn.exec(
                    "CREATE TABLE IF NOT EXISTS " + tableName + " ("
                    "id SERIAL PRIMARY KEY, "
                    "nameSensor VARCHAR(100), "
                    "current NUMERIC(10, 2), "
                    "voltage NUMERIC(10, 2), "
                    "activePower NUMERIC(10, 2), "
                    "reactivePower NUMERIC(10, 2), "
                    "ipAddress INET, "
                    "timestamp TIMESTAMPTZ"
                    ");"
                );
                std::cout << "Table created successfully!" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    
        // Додавання запису (поки як приклад)
        // std::string nameSensor = "Sensor_1";
        // double current = 0.5, voltage = 220.0, activePower = 10.0, reactivePower = 5.0;
        // std::string ipAddress = "192.168.1.1";
        // std::string timestamp = "2024-10-27T10:00:00Z";

        // std::string query = 
        //     "INSERT INTO " + tableName + " ("
        //     "nameSensor, current, voltage, activePower, reactivePower, ipAddress, timestamp"
        //     ") VALUES ("
        //     "'" + nameSensor + "', " + std::to_string(current) + ", " + 
        //     std::to_string(voltage) + ", " + std::to_string(activePower) + ", " + 
        //     std::to_string(reactivePower) + ", '" + ipAddress + "', '" + timestamp + "'"
        //     ");";

        // txn.exec(query);
        // std::cout << "Record inserted successfully!" << std::endl;

        // Закриття підключення
        // conn.disconnect();

    } else {
        std::cerr << "Invalid Host Name!\n";
    }
}

