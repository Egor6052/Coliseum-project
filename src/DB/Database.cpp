#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
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
            return "No sensor data found in the database.";
        }

        // Generating output
        std::string sensorData;
        for (const auto& row : res) {
            int id = row["id"].as<int>();
            std::string date = row["date"].as<std::string>();
            std::string ipAddress = row["ip_address"].as<std::string>();
            std::string sensorName = row["sensor_name"].as<std::string>();
            float current = row["current"].as<float>();
            float voltage = row["voltage"].as<float>();
            float activePower = row["active_power"].as<float>();
            float reactivePower = row["reactive_power"].as<float>();

            sensorData += "ID: " + std::to_string(id) + "\n";
            sensorData += "  Date: " + date + "\n";
            sensorData += "  IP Address: " + ipAddress + "\n";
            sensorData += "  Sensor Name: " + sensorName + "\n";
            sensorData += "  Current: " + std::to_string(current) + " A\n";
            sensorData += "  Voltage: " + std::to_string(voltage) + " V\n";
            sensorData += "  Active Power: " + std::to_string(activePower) + " W\n";
            sensorData += "  Reactive Power: " + std::to_string(reactivePower) + " VAR\n";
            // sensorData += "---------------------------------------------\n";
        }

        return sensorData;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return "Error retrieving sensor data.";
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
