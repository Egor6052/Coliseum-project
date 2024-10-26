#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>

class Server {
private:
    int aPort;
    int m_port;
    int m_socket;

    std::string m_certificate_path;
    std::string m_key_path;
    std::string m_ca_path;

    std::string m_html_data;

    std::string m_start_data_time;
    size_t m_get_request_count { 0 };

    const SSL_METHOD *mp_sslmethod { nullptr };
    SSL_CTX *mp_ssl_context { nullptr };

    std::vector<char> m_fav_icon_buffer;

    bool _ssl_init();
    bool _socket_init();
    void _client_processing(int aSocket, std::string aIp);

public:
    Server();
    ~Server();

    bool start();

    void setCertPath(const std::string &aPath);
    void setKeyPath(const std::string &aPath);
    void setPathForCA(const std::string &aPath);
};

#endif // ISENDDATA_H
