#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include "Database.h"

class Server : public Database {
private:
    std::string configFilePath;
    int port;
    std::string host_name;

    net::io_context io_context_;
    tcp::acceptor acceptor_;

public:
    Server();
    ~Server();

    void Configuration();

    // http
    void run();
    void accept();
    void handleClient(std::shared_ptr<tcp::socket> socket);
    void process_request(std::shared_ptr<tcp::socket> socket, const http::request<http::string_body>& req);
    
    // Retrieving the request body
    std::string getRequestBody(const std::string& request);

    // Getting a parameter from the request body
    std::string extractParameter(const std::string& body, const std::string& param);

    void RS485();
    void start();

};

#endif