#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

// Налаштування CORS
void Server::setupCORS(httplib::Server &svr) {
    svr.set_pre_routing_handler([](const httplib::Request &req, httplib::Response &res) {
        std::cout << "Отримано запит: " << req.method << " " << req.path << std::endl;

        res.set_header("Access-Control-Allow-Origin", "http://0.0.0.0:5173");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
        res.set_header("Access-Control-Allow-Credentials", "true");

        if (req.method == "OPTIONS") {
            res.status = 204; // No Content
            return httplib::Server::HandlerResponse::Handled;
        }

        return httplib::Server::HandlerResponse::Unhandled;
    });
}
