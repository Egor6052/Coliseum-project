#pragma once
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

// http://localhost:8080/api/data

class HTTP {
private:
    int port;
    std::string pathToJson;
    // std::string RESPONSE;;

public:
    HTTP();
    std::string readJsonFile(const std::string& path);
    void handleClient(tcp::socket socket);
    void start();
};

#endif
