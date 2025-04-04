#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include <thread>
#include "../../lib/http/httplib.h"
#include <json/json.h>

#include "Logger.h"
#include "Database.h"

class Server : public Database {
private:
    std::string configFilePath;
    int port;
    std::string ip;
    std::string host_name;
    httplib::Server svr;
    std::map<std::string, std::string> configValues;

public:
    Server();
    ~Server();

    void Configuration();
    void ConfigFields();

    // http
    void http_start();
    void http_server(const httplib::Request& req, httplib::Response& res);

    // void run();
    // void accept();
    // void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    // void process_request(std::shared_ptr<boost::asio::ip::tcp::socket> socket, 
    // const boost::beast::http::request<boost::beast::http::string_body>& req);
    
    // Retrieving the request body
    // std::string getRequestBody(const std::string& request);

    // Getting a parameter from the request body
    // std::string extractParameter(const std::string& body, const std::string& param);
    
    void createCSV(const std::string& filename);
    void sendToEmail(const std::string& recipient, const std::string& filename);
    void RS485();
    // void start();

};

#endif