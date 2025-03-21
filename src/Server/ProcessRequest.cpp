// #include <boost/beast/core.hpp>
// #include <boost/beast/http.hpp>
// #include <boost/asio.hpp>
// #include <nlohmann/json.hpp>
// #include <iostream>
// #include <memory>
// #include <string>

// #include "../headers/Server.h"

// namespace beast = boost::beast;
// namespace http = beast::http;
// namespace net = boost::asio;
// using tcp = net::ip::tcp;
// using json = nlohmann::json;

// void Server::process_request(std::shared_ptr<tcp::socket> socket, const http::request<http::string_body>& req) {
//         http::response<http::string_body> res{http::status::ok, req.version()};
//         res.set(http::field::content_type, "application/json");

//         // Routing
//         std::string target = std::string(req.target());

//         if (target == "/api/get_data" && req.method() == http::verb::get) {
//             // TODO
//             json data = getData();;
//             res.body() = data.dump();
//         }
//         else if (target == "/api/all_users" && req.method() == http::verb::get) {
//             // TODO
            
//             json users = {{"users", {{"id", 1, "name", "John"}, {"id", 2, "name", "Jane"}}}};

//             res.body() = users.dump();
//         }
//         else if (target == "/api/registration" && req.method() == http::verb::post) {
//             json request_body = json::parse(req.body(), nullptr, false);
//             if (!request_body.is_discarded()) {
//                 std::string name = request_body["name"];
//                 std::string password = request_body["password"];
//                 // TODO
//                 // registerAsUser(name, password); // Реєстрація в БД
//                 res.body() = json{{"status", "success"}, {"message", "User registered"}}.dump();
//             } else {
//                 res.result(http::status::bad_request);
//                 res.body() = json{{"error", "Invalid JSON"}}.dump();
//             }
//         }
//         else if (target == "/api/login" && req.method() == http::verb::post) {
//             json request_body = json::parse(req.body(), nullptr, false);
//             if (!request_body.is_discarded()) {
//                 std::string name = request_body["name"];
//                 std::string password = request_body["password"];
//                 // TODO
//                 // Перевірка логіну
//                 res.body() = json{{"status", "success"}, {"token", "example_token"}}.dump();
//             } else {
//                 res.result(http::status::bad_request);
//                 res.body() = json{{"error", "Invalid JSON"}}.dump();
//             }
//         }
//         else {
//             res.result(http::status::not_found);
//             res.body() = json{{"error", "Not Found"}}.dump();
//         }

//         res.prepare_payload();
//         http::async_write(*socket, res, [socket](beast::error_code ec, std::size_t) {});
//     }