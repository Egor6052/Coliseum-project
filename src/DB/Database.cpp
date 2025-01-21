#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "../../lib/Database.h"

Database::Database(){
    this->data = "";
    this->ipAddress = "";
    this->nameSensor = "Sensor1";
    this->current = 0.0f;
    this->voltage = 0.0f;
    this->activePower = 0.0f;
    this->reactivePower = 0.0f;
}
Database::~Database(){
}

void Database::setData(){

    try {
        this->data = getCurrentDateTime();
        this->ipAddress = getIpAddress();
        this->nameSensor = getNameSensor();
        this->current = getCurrent();
        this->voltage = getVoltage();
        this->activePower = getActivePower();
        this->reactivePower = getReactivePower();

        pqxx::connection conn("dbname=sensordata user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

            if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
            }

        pqxx::work txn(conn);

        // Inserting data
        std::string query = 
            "INSERT INTO public.sensordata (date, ip_address, sensor_name, current, voltage, active_power, reactive_power) "
            "VALUES ($1, $2, $3, $4, $5, $6, $7)";

        txn.exec_params(
            query,
            data,
            ipAddress,
            nameSensor,
            current,
            voltage,
            activePower,
            reactivePower
        );

        txn.commit();
        std::cout << "\033[36m Data saved successfully!\033[0m" << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

std::string Database::getData() {
    try {
        pqxx::connection conn("dbname=sensordata user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Running a SQL query to retrieve all records
        pqxx::work txn(conn);
        pqxx::result res = txn.exec(
            "SELECT id, date, ip_address, sensor_name, current, voltage, active_power, reactive_power "
            "FROM public.sensordata ORDER BY id DESC;"
        );

        if (res.empty()) {
            nlohmann::json response = {{"message", "No sensor data found in the database."}};
            return response.dump(4);
        }

        // Створення JSON-масиву для зберігання даних
        nlohmann::json jsonData = nlohmann::json::array();

        // Обробка рядків результату
        for (const auto& row : res) {
            nlohmann::json sensor = {
                {"id", row["id"].as<int>()},
                {"date", row["date"].as<std::string>()},
                {"ip_address", row["ip_address"].as<std::string>()},
                {"sensor_name", row["sensor_name"].as<std::string>()},
                {"current", row["current"].as<float>()},
                {"voltage", row["voltage"].as<float>()},
                {"active_power", row["active_power"].as<float>()},
                {"reactive_power", row["reactive_power"].as<float>()}
            };

            jsonData.push_back(sensor);
        }

        return jsonData.dump(4);

    } catch (const std::exception& e) {
        nlohmann::json errorResponse = {
            {"error", e.what()}
        };
        return errorResponse.dump(4);
    }
}

void Database::deleteData(std::string valueID) {
    try {
        pqxx::connection conn("dbname=sensordata user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Executing an SQL query to delete a record from a table by ID
        pqxx::work txn(conn);
        txn.exec_params("DELETE FROM public.SensorData WHERE id = $1;", valueID);

        txn.commit();
        std::cout << "\033[36mNote with ID " << valueID << " deleted successfully.\033[0m" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
