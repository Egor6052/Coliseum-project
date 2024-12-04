#include <boost/asio.hpp>
#include "HTTP_server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;
using json = nlohmann::json;

HTTP::HTTP() {
    port = 8080;
    pathToJson = "../database/data.json";
}

// Getting all the data
std::string HTTP::readJsonFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return jsonData;
}

// Search by ID
std::string HTTP::getSensorById(const std::string& id) {
    std::string jsonData = readJsonFile(pathToJson);
    if (jsonData.empty()) {
        return "";
    }

    json sensors = json::parse(jsonData);
    for (const auto& sensor : sensors) {
        if (sensor["id"] == id) {
            return sensor.dump();
        }
    }
    return "";
}

// Search by name
std::string HTTP::getSensorByName(const std::string& name) {
    std::string jsonData = readJsonFile(pathToJson);
    if (jsonData.empty()) {
        return "";
    }

    json sensors = json::parse(jsonData);
    json matchedSensors = json::array();
    for (const auto& sensor : sensors) {
        if (sensor["nameSensor"].get<std::string>().find(name) != std::string::npos) {
            matchedSensors.push_back(sensor);
        }
    }
    return matchedSensors.dump();
}

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
            // Getting all the data
            response_body = readJsonFile(pathToJson);

            if (response_body.empty()) {
                response_body =
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 16\r\n\r\n"
                    "404 File Not Found";
            } else {
                response_body =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: " + std::to_string(response_body.size()) + "\r\n\r\n" +
                    response_body;
            }

        } else if (request.find("GET /api/data/") != std::string::npos) {
            if (request.find("GET /api/data/name/") != std::string::npos) {
                // Search by name
                std::string name = request.substr(request.find("/api/data/name/") + 16);
                name = name.substr(0, name.find(" "));
                
                std::string sensorData = getSensorByName(name);

                if (sensorData.empty()) {
                    response_body =
                        "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 16\r\n\r\n"
                        "404 Not Found";
                } else {
                    response_body =
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + std::to_string(sensorData.size()) + "\r\n\r\n" +
                        sensorData;
                }

            } else {
                // Search by ID
                std::string id = request.substr(request.find("/api/data/id/") + 13);
                id = id.substr(0, id.find(" "));

                std::string sensorData = getSensorById(id);

                if (sensorData.empty()) {
                    response_body =
                        "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/plain\r\n"
                        "Content-Length: 16\r\n\r\n"
                        "404 File Not Found";
                } else {
                    response_body =
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: " + std::to_string(sensorData.size()) + "\r\n\r\n" +
                        sensorData;
                }
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


void HTTP::start() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        printf("The HTTP server is running...\n");
        printf("\033[32m http://localhost:%d/api/data \033[0m\n", port);

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(&HTTP::handleClient, this, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}
