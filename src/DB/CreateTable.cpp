#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/Database.h"


void Database::CreateTable() {
    try {
        std::string connectionString = "dbname=sensordata user=" + getUserName() + " password=" + getUserPassword() + " host=localhost";

        pqxx::connection conn(connectionString);

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Checking if a table exists
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT to_regclass('public.SensorData');");

        if (res[0][0].is_null()) {
            // If the table does not exist, create it
            std::string createTableQuery = R"(
                CREATE TABLE public.SensorData (
                    id SERIAL PRIMARY KEY,
                    date TIMESTAMP,
                    ip_address VARCHAR(255) NOT NULL,
                    sensor_name VARCHAR(255) NOT NULL,
                    current FLOAT NOT NULL,
                    voltage FLOAT NOT NULL,
                    active_power FLOAT NOT NULL,
                    reactive_power FLOAT NOT NULL
                );
            )";
            txn.exec(createTableQuery);
            txn.commit();
            std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable 'SensorData' created successfully!\033[35m⊹₊⟡⋆\033[0m\n" << std::endl;
        } else {
            std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable 'SensorData' already exists!\033[35m⊹₊⟡⋆\033[0m\n" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
