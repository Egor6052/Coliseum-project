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
    // std::string getCommonHeader();
    // std::string getCommonFooter();
    // std::string readFile(const std::string& path);
    void http_start();
    void http_server(const httplib::Request& req, httplib::Response& res);
    
    void createCSV(const std::string& filename);
    void sendToEmail(const std::string& recipient, const std::string& filename);
    void RS485();
    // void start();

};

#endif