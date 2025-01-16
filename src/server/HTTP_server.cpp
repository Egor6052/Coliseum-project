#include <boost/asio.hpp>
#include "HTTP_server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;
using json = nlohmann::json;

HTTP::HTTP() : dbConnection("dbname=test user=postgres password=secret host=localhost port=5432") {
    port = 8080;
    if (!dbConnection.is_open()) {
        throw std::runtime_error("Failed to connect to the database.");
    }
}

// Отримання всіх сенсорів
json HTTP::fetchAllSensors() {
    pqxx::work txn(dbConnection);
    pqxx::result result = txn.exec("SELECT * FROM sensors");
    json sensors = json::array();

    for (const auto& row : result) {
        json sensor;
        sensor["id"] = row["id"].as<std::string>();
        sensor["nameSensor"] = row["name"].as<std::string>();
        sensor["value"] = row["value"].as<std::string>();
        sensors.push_back(sensor);
    }

    return sensors;
}

// Пошук сенсора за ID
json HTTP::getSensorById(const std::string& id) {
    pqxx::work txn(dbConnection);
    pqxx::result result = txn.exec_params("SELECT * FROM sensors WHERE id = $1", id);

    if (result.empty()) {
        return nullptr;
    }

    json sensor;
    sensor["id"] = result[0]["id"].as<std::string>();
    sensor["nameSensor"] = result[0]["name"].as<std::string>();
    sensor["value"] = result[0]["value"].as<std::string>();

    return sensor;
}

// Пошук сенсорів за ім'ям
json HTTP::getSensorByName(const std::string& name) {
    pqxx::work txn(dbConnection);
    pqxx::result result = txn.exec_params("SELECT * FROM sensors WHERE name LIKE $1", "%" + name + "%");
    json sensors = json::array();

    for (const auto& row : result) {
        json sensor;
        sensor["id"] = row["id"].as<std::string>();
        sensor["nameSensor"] = row["name"].as<std::string>();
        sensor["value"] = row["value"].as<std::string>();
        sensors.push_back(sensor);
    }

    return sensors;
}

// Обробка клієнтських запитів
void HTTP::handleClient(tcp::socket socket) {
    try {
        char buffer[1024];
        boost::system::error_code error;
        socket.read_some(boost::asio::buffer(buffer), error);

        if (error == boost::asio::error::eof) {
            return;
        } else if (error) {
            throw boost::system::system_error(error);
        }

        std::string request(buffer);
        std::string response_body;

        if (request.find("GET /api/data ") != std::string::npos) {
            // Всі дані
            json sensors = fetchAllSensors();
            response_body =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: " + std::to_string(sensors.dump().size()) + "\r\n\r\n" +
                sensors.dump();

        } else if (request.find("GET /api/data/id/") != std::string::npos) {
            // Пошук за ID
            std::string id = request.substr(request.find("/api/data/id/") + 13);
            id = id.substr(0, id.find(" "));
            json sensor = getSensorById(id);

            if (sensor.is_null()) {
                response_body =
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 16\r\n\r\n"
                    "404 Not Found";
            } else {
                response_body =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: " + std::to_string(sensor.dump().size()) + "\r\n\r\n" +
                    sensor.dump();
            }

        } else if (request.find("GET /api/data/name/") != std::string::npos) {
            // Пошук за ім'ям
            std::string name = request.substr(request.find("/api/data/name/") + 16);
            name = name.substr(0, name.find(" "));
            json sensors = getSensorByName(name);

            if (sensors.empty()) {
                response_body =
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 16\r\n\r\n"
                    "404 Not Found";
            } else {
                response_body =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: " + std::to_string(sensors.dump().size()) + "\r\n\r\n" +
                    sensors.dump();
            }

        } else {
            response_body =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 13\r\n\r\n"
                "404 Not Found";
        }

        boost::asio::write(socket, boost::asio::buffer(response_body), error);

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

