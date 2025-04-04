#include <iostream>
#include <thread>
#include "../headers/Server.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>

void Server::http_start() {
    svr.Post("/command", [this](const httplib::Request& req, httplib::Response& res) {
        http_server(req, res);
    });

    std::thread server_thread([this]() {
        svr.listen("0.0.0.0", 8080);
    });

    server_thread.detach();
}

void Server::http_server(const httplib::Request& req, httplib::Response& res) {
    if (req.method != "POST") {
        res.status = 405;
        res.set_content("{\"error\":\"Method Not Allowed\"}", "application/json");
        return;
    }

    Json::Value jsonData;
    Json::Reader reader;
    if (!reader.parse(req.body, jsonData) || !jsonData.isMember("command") || !jsonData.isMember("value")) {
        res.status = 400;
        res.set_content("{\"error\":\"Invalid JSON or missing fields\"}", "application/json");
        return;
    }

    std::string command = jsonData["command"].asString();
    int value = jsonData["value"].asInt();

    std::cout << getLoggerDateTime() << " | Command: " << command << ", Value: " << value << " | ";

    if (command == "start") {
        std::cout << "START action executed" << std::endl;
    } else if (command == "stop") {
        std::cout << "STOP action executed" << std::endl;
    } else {
        res.status = 400;
        res.set_content("{\"error\":\"Unknown command\"}", "application/json");
        return;
    }

    res.set_content("{\"status\":\"OK\"}", "application/json");
}