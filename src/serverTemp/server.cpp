 
#include "server.h"

Server::Server() : aPort(443), m_port(aPort), m_socket(-1) {
    // Можна додати ініціалізацію або вивід повідомлень для налагодження
}

Server::~Server() {
    // Звільнення ресурсів, якщо потрібно
}

bool Server::start() {
    if (!_ssl_init()) {
        std::cerr << "SSL initialization failed." << std::endl;
        return false;
    }
    if (!_socket_init()) {
        std::cerr << "Socket initialization failed." << std::endl;
        return false;
    }
    return true;
}

bool Server::_ssl_init() {
    // Ініціалізація SSL
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    mp_sslmethod = SSLv23_server_method();
    mp_ssl_context = SSL_CTX_new(mp_sslmethod);

    if (!mp_ssl_context) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    return true;
}

bool Server::_socket_init() {
    // Ініціалізація сокету
    return true;
}

void Server::_client_processing(int aSocket, std::string aIp) {
    // Обробка клієнтських підключень
}

void Server::setCertPath(const std::string &aPath) {
    m_certificate_path = aPath;
}

void Server::setKeyPath(const std::string &aPath) {
    m_key_path = aPath;
}

void Server::setPathForCA(const std::string &aPath) {
    m_ca_path = aPath;
}
