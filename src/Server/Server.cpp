#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "Server.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

Server::Server() {
    this->configFilePath = "../../configurations/configFile.conf";    
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
    serverThread.join(); 

}

void Server::run() {
    accept();
    io_context_.run();
}

void Server::accept() {
        auto socket = std::make_shared<tcp::socket>(io_context_);
        acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
            if (!ec) {
                handle_client(socket);
            }
            accept();
        });
    }


void Server::handleClient(std::shared_ptr<tcp::socket> socket) {
    auto buffer = std::make_shared<beast::flat_buffer>();
    auto req = std::make_shared<http::request<http::string_body>>();

    http::async_read(*socket, *buffer, *req,
        [this, socket, req](beast::error_code ec, std::size_t) {
            if (!ec) {
                process_request(socket, *req);
            }
            socket->shutdown(tcp::socket::shutdown_send, ec);
        });
}

