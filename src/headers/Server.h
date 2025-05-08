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
#include "Accounts.h"

class Server : public Database {
private:
    Accounts account;
    std::string configFilePath;
    int port;
    std::string ip;

    std::string keyAccess;
    std::string keyRefresh;

    std::string host_name;
    httplib::Server svr;
    std::map<std::string, std::string> configValues;

public:
    Server();
    ~Server();

    void Configuration();
    void ConfigFields();

    std::string getKeyAccess();
    std::string getKeyRefresh();


    // http
    // std::string getCommonHeader();
    // std::string getCommonFooter();
    // std::string readFile(const std::string& path);
    void http_start();
    // void http_server(const httplib::Request& req, httplib::Response& res);
    
    void handleAuthRequest(const httplib::Request &req, httplib::Response &res, const std::string &endpoint);
    void setupStaticFiles(httplib::Server &svr);
    void createCSV(const std::string& filename);
    void setupCORS(httplib::Server &svr);
    void handleClientRoutes(const httplib::Request &req, httplib::Response &res);
    void shandleLogoutRequest(const httplib::Request &req, httplib::Response &res);
    void handleLogoutAllRequest(const httplib::Request &req, httplib::Response &res);
    void handleRefreshTokenRequest(const httplib::Request &req, httplib::Response &res);

    void sendToEmail(const std::string& recipient, const std::string& filename);
    

};

#endif