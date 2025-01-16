#pragma once
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

// http://localhost:8080/api/data

class HTTP {
public:
    HTTP();
    void start();

private:
    int port;
    std::string dbConnString;
    pqxx::connection dbConnection;

    json fetchAllSensors();
    json getSensorById(const std::string& id);
    json getSensorByName(const std::string& name);
    void handleClient(tcp::socket socket);
};

#endif
