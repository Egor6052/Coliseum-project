#include <iostream>
#include <cstring>
#include <thread>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Server.h"

Server::Server() {
    this->port = 8080;
    this->host_name = "localhost";
}

Server::~Server() {}

void Server::handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    read(clientSocket, buffer, sizeof(buffer) - 1);
    std::cout << "Request:\n" << buffer << std::endl;

    std::string request(buffer);
    



    if (request.find("GET /api/data") != std::string::npos) {
        // /api/data
        std::string body = getData();
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            body;

        send(clientSocket, response.c_str(), response.size(), 0);
    } 
if (request.find("GET /api/reg") != std::string::npos) {
    std::ifstream file("../Front/index.html");
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string htmlContent = buffer.str();

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + std::to_string(htmlContent.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            htmlContent;

        send(clientSocket, response.c_str(), response.size(), 0);
    } else {
        std::string response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>404 Not Found</h1></body></html>";
        send(clientSocket, response.c_str(), response.size(), 0);
    }
}

    if (request.find("POST /api/register") != std::string::npos) {
        std::string body = getRequestBody(request);
        std::string name = extractParameter(body, "name");
        std::string password = extractParameter(body, "password");

        // registerAsUser(name, password);

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"           
            "Connection: close\r\n"
            "\r\n"
            "User registered successfully!";

        send(clientSocket, response.c_str(), response.size(), 0);
        return;
    }
    else {
        std::string response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>404 Not Found</h1></body></html>";

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    close(clientSocket);
}


// Функція для витягування тіла запиту
std::string Server::getRequestBody(const std::string& request) {
    size_t bodyStart = request.find("\r\n\r\n");
    if (bodyStart != std::string::npos) {
        return request.substr(bodyStart + 4);
    }
    return "";
}

// Функція для отримання параметра з тіла запиту
std::string Server::extractParameter(const std::string& body, const std::string& param) {
    size_t paramPos = body.find(param + "=");
    if (paramPos != std::string::npos) {
        size_t startPos = paramPos + param.length() + 1;
        size_t endPos = body.find("&", startPos);
        if (endPos == std::string::npos) {
            endPos = body.length();
        }
        return body.substr(startPos, endPos - startPos);
    }
    return "";
}

