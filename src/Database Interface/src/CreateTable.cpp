#include <pqxx/pqxx> 
#include "../lib/User.h"

void User::CreateTable(std::string valueAnswer){
        if (!valueAnswer.empty() && valueAnswer.length() <= 50) {

        // Підключення до бази даних
        pqxx::connection conn("dbname=server user=" + getUserName() + " password="+getUserPassword() + " host=localhost");
        if (conn.is_open()) {
            std::cout << "Connected to database successfully: " << conn.dbname() << std::endl;
        } else {
            std::cerr << "Failed to connect to database!" << std::endl;
            return 1;
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
            }
            
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
        catch (const std::exception& e) {
            std::cerr << "Invalid table name!" << '\n';
        }
    
        // // Додавання запису
        // txn.exec("INSERT INTO test_table (name, age) VALUES ('John Doe', 30);");
        // std::cout << "Record inserted successfully!" << std::endl;

        // Застосування змін
        // txn.commit();
        // std::cout << "Transaction committed successfully!" << std::endl;

        // Закриття підключення
        conn.disconnect();

    } else {
        std::cerr << "Invalid Host Name!\n";
    }
}

