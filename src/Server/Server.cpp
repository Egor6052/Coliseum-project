#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../headers/Server.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

Server::Server() {
    this->configFilePath = "../../config/configFile.conf";    
    this->port = 8080;
    this->host_name = "localhost";

    Configuration();
}

// TODO
// /api/get_data = то всі записи датчиків.
// /api/all_users = список користувачів з бд.

// /api/registration = на реєстрацію. Зареєструвати користувача та отримати відповідь
// /api/login = на вхід. Передати на сервер данні для входу для перевірки, та отримати відповідь
// /api/remove_data = видалиння записів Передати на сервер id запису, який видалиться
// /api/backup = показати бекапи з бд. Можна буде створити бекап, треба на сервері визвати функцію.

Server::~Server() { 
    // if (serverThread.joinable()) {
        // serverThread.join();
    // }
}

// void Server::run() {
//     serverThread = std::thread([this]() {
//         accept(); 
//         io_context_.run();
//     });
// }

// void Server::accept() {
//     auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
//     acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& ec) {
//         if (!ec) {
//             handleClient(socket);
//         }
//         accept();
//     });
// }

void Server::handleClient(std::shared_ptr<tcp::socket> socket) {
    auto buffer = std::make_shared<beast::flat_buffer>();
    auto req = std::make_shared<http::request<http::string_body>>();

    http::async_read(*socket, *buffer, *req,
        [this, socket, req](beast::error_code ec, std::size_t) {
            if (!ec) {
                // process_request(socket, *req);
            }
            socket->shutdown(tcp::socket::shutdown_send, ec);
        });
}

