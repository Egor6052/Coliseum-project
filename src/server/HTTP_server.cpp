#include <boost/asio.hpp>
#include "HTTP_server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

HTTP::HTTP(){
    port = 8080;
    pathToJson = "../database/data.json";
}

std::string HTTP::readJsonFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }

    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return jsonData;
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

        // Обробка HTTP-запиту
        std::string request(buffer);
        std::string response_body;

        if (request.find("GET /api/data") != std::string::npos) {
            // Читаємо JSON-файл
            std::string jsonData = readJsonFile(pathToJson);

            if (jsonData.empty()) {
                std::string response =
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 16\r\n\r\n"
                    "404 File Not Found";
                boost::asio::write(socket, boost::asio::buffer(response), error);
                return;
            }

            std::string response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: " + std::to_string(jsonData.size()) + "\r\n\r\n" +
                jsonData;

            boost::asio::write(socket, boost::asio::buffer(response), error);
        } else {
            std::string response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 13\r\n\r\n"
                "404 Not Found";
            boost::asio::write(socket, boost::asio::buffer(response), error);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void HTTP::start() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        std::cout << "HTTP сервер запущено на порту " << port << "..." << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(&HTTP::handleClient, this, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Помилка сервера: " << e.what() << std::endl;
    }
}
