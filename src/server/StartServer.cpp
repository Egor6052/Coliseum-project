#include <boost/asio.hpp>
#include "HTTP_server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>

void HTTP::start() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        std::cout << "The HTTP server is running...\n";
        std::cout << "\033[32m http://localhost:" << port << "/api/data \033[0m\n";

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(&HTTP::handleClient, this, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}