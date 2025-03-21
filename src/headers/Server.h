#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string.h>
#include <memory>
#include <unordered_map>
#include <thread>

#include "Database.h"

class Server : public Database {
private:
    std::string configFilePath;
    int port;
    std::string host_name;
    std::unordered_map<std::string, std::string> configValues;

    // boost::asio::io_context io_context_;
    // boost::asio::ip::tcp::acceptor acceptor_;
    // std::thread serverThread;

public:
    Server();
    ~Server();

    void Configuration();
    void ConfigFields();

    // http
    // void run();
    // void accept();
    void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    // void process_request(std::shared_ptr<boost::asio::ip::tcp::socket> socket, 
    // const boost::beast::http::request<boost::beast::http::string_body>& req);
    
    // Retrieving the request body
    // std::string getRequestBody(const std::string& request);

    // Getting a parameter from the request body
    // std::string extractParameter(const std::string& body, const std::string& param);
    
    void RS485();
    void start();

};

#endif