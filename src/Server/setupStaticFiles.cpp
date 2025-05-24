#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
// #include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <nlohmann/json.hpp>

// Налаштування MIME-типів і статичних файлів
void Server::setupStaticFiles(httplib::Server &svr) {
    svr.set_mount_point("/client", "../client/dist");

    svr.set_file_extension_and_mimetype_mapping("js", "text/javascript");
    svr.set_file_extension_and_mimetype_mapping("css", "text/css");
    svr.set_file_extension_and_mimetype_mapping("html", "text/html");
    svr.set_file_extension_and_mimetype_mapping("json", "application/json");
    svr.set_file_extension_and_mimetype_mapping("png", "image/png");
    svr.set_file_extension_and_mimetype_mapping("jpg", "image/jpeg");
    svr.set_file_extension_and_mimetype_mapping("svg", "image/svg+xml");
}