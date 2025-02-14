// #include <iostream>
// #include <mysql/mysql.h>
// #include "../../lib/UserDB.h"

// void UserDB::createMySQLUser() {
//     MYSQL *conn;
//     conn = mysql_init(nullptr);

//     if (!conn) {
//         std::cerr << "MySQL initialization failed!\n";
//         return;
//     }

//     // Підключення як root
//     if (!mysql_real_connect(conn, "localhost", "root", getAdminPassword().c_str(), nullptr, 0, nullptr, 0)) {
//         std::cerr << "Connection failed: " << mysql_error(conn) << '\n';
//         mysql_close(conn);
//         return;
//     }

//     // Створення бази даних, якщо не існує
//     std::string createDatabaseQuery = "CREATE DATABASE IF NOT EXISTS " + getDBName();
//     if (mysql_query(conn, createDatabaseQuery.c_str())) {
//         std::cerr << "Database creation failed: " << mysql_error(conn) << '\n';
//     }

//     // Переключення на базу
//     if (mysql_select_db(conn, getDBName().c_str())) {
//         std::cerr << "Database selection failed: " << mysql_error(conn) << '\n';
//     }

//     // Створення користувача для додатка, якщо не існує
//     std::string createUserQuery = "CREATE USER IF NOT EXISTS '" + getUserDBName() + "'@'localhost' IDENTIFIED BY '" + getUserDBPassword() + "';";
//     if (mysql_query(conn, createUserQuery.c_str())) {
//         std::cerr << "User creation failed: " << mysql_error(conn) << '\n';
//     }

//     // Надання привілеїв
//     std::string grantQuery = "GRANT ALL PRIVILEGES ON " + getDBName() + ".* TO '" + getUserDBName() + "'@'localhost';";
//     if (mysql_query(conn, grantQuery.c_str())) {
//         std::cerr << "Granting privileges failed: " << mysql_error(conn) << '\n';
//     }

//     // Створення таблиці SensorData
//     std::string createTableQuery =
//         "CREATE TABLE IF NOT EXISTS " + getDBName() + " ("
//         "id INT AUTO_INCREMENT PRIMARY KEY, "
//         "date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
//         "ip_address VARCHAR(255) NOT NULL, "
//         "sensor_name VARCHAR(255) NOT NULL, "
//         "current FLOAT NOT NULL, "
//         "voltage FLOAT NOT NULL, "
//         "active_power FLOAT NOT NULL, "
//         "reactive_power FLOAT NOT NULL"
//     ");";


//     if (mysql_query(conn, createTableQuery.c_str())) {
//         std::cerr << "Table creation failed: " << mysql_error(conn) << '\n';
//     }

//     std::cout << "MySQL setup completed successfully!\n";
//     mysql_close(conn);
// }
