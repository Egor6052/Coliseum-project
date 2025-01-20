#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/UserDB.h"

void UserDB::createPostgresUser(const std::string& adminPassword) {
    try {
        // Підключення до PostgreSQL як адміністратор для створення бази даних
        std::string adminConnectionString = "dbname=postgres user=postgres password=" + adminPassword + " host=localhost";
        pqxx::connection conn(adminConnectionString);

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to the database as admin!");
        }

        // Перевірка, чи існує база даних sensordata
        pqxx::work txn1(conn);
        std::string checkDbQuery = "SELECT 1 FROM pg_database WHERE datname = 'sensordata';";
        pqxx::result checkDbResult = txn1.exec(checkDbQuery);

        if (checkDbResult.empty()) {
            // База даних не існує, створюємо її
            std::string createDbQuery = "CREATE DATABASE sensordata;";
            txn1.exec(createDbQuery);
            txn1.commit();
            std::cout << "\033[36m Database 'sensordata' created successfully!\033[0m" << std::endl;
        } else {
            // std::cout << "\033[36m Database 'sensordata' already exists.\033[0m" << std::endl;
        }

        // Підключення до нової бази даних sensordata
        std::string connectionString = "dbname=sensordata user=postgres password=" + adminPassword + " host=localhost";
        pqxx::connection conn2(connectionString);

        if (!conn2.is_open()) {
            throw std::runtime_error("Failed to connect to the 'sensordata' database!");
        }

        // Створення нового користувача або перевірка, чи існує вже
        pqxx::work txn2(conn2);

        // Перевірка, чи існує вже роль з таким ім'ям
        std::string checkUserQuery = "SELECT 1 FROM pg_roles WHERE rolname = '" + name + "';";
        pqxx::result checkResult = txn2.exec(checkUserQuery);

        if (checkResult.empty()) {
            // Якщо роль не існує, створюємо її
            std::string createUserQuery = "CREATE USER " + name + " WITH PASSWORD '" + password + "';";
            txn2.exec(createUserQuery);
            std::cout << "\033[36m User '" << name << "' created successfully!\033[0m" << std::endl;
        } else {
            // std::cout << "\033[36m Role '" << name << "' already exists.\033[0m" << std::endl;
        }

        // Надання прав на базу даних sensordata
        std::string grantDbPrivilegesQuery = "GRANT ALL PRIVILEGES ON DATABASE sensordata TO " + name + ";";
        txn2.exec(grantDbPrivilegesQuery);
        txn2.commit();
        // std::cout << "\033[36m Privileges granted to user '" << name << "' on database 'sensordata'.\033[0m" << std::endl;

        // Надання прав на таблиці
        pqxx::work txn3(conn2);

        // Перевірка доступу до схеми public
        std::string checkSchemaAccessQuery = "SELECT has_schema_privilege('" + name + "', 'public', 'CREATE');";
        pqxx::result schemaAccessResult = txn3.exec(checkSchemaAccessQuery);

        if (schemaAccessResult.empty() || !schemaAccessResult[0][0].as<bool>()) {
            // Якщо користувач не має прав на створення в схемі public
            std::string grantSchemaPrivilegesQuery = "GRANT CREATE ON SCHEMA public TO " + name + ";";
            txn3.exec(grantSchemaPrivilegesQuery);
            txn3.commit();
            std::cout << "\033[36m Privileges granted to user '" << name << "' on schema 'public'.\033[0m" << std::endl;
        }

        // Створення таблиці, якщо її ще немає
        std::string createTableQuery = "CREATE TABLE IF NOT EXISTS public.SensorData (id SERIAL PRIMARY KEY, data JSONB);";
        txn3.exec(createTableQuery);

        // Надання прав на таблицю
        std::string grantTablePrivilegesQuery = "GRANT ALL PRIVILEGES ON TABLE public.SensorData TO " + name + ";";
        txn3.exec(grantTablePrivilegesQuery);
        txn3.commit();
        // std::cout << "\033[36m Privileges granted to user '" << name << "' on table 'public.SensorData'.\033[0m" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}