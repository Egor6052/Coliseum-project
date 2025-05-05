// #include <cpr/cpr.h>
// #include <nlohmann/json.hpp>
// #include "../headers/Accounts.h"

// using json = nlohmann::json;

// // Авторизація користувача
// void Accounts::handleLoginFromAPI() {
//     try {
//         // Звернення до REST API для отримання даних
//         cpr::Response response = cpr::Get(cpr::Url{"http://localhost:5173/api/auth/login-data"});

//         // Перевірка статусу відповіді
//         if (response.status_code != 200) {
//             std::cerr << "Помилка при зверненні до REST API: " << response.status_code << "\n";
//             std::cerr << "Відповідь сервера: " << response.text << "\n";
//             return;
//         }

//         // Парсинг JSON із відповіді
//         json responseData = json::parse(response.text);

//         // Перевірка наявності необхідних полів
//         if (!responseData.contains("email") || !responseData.contains("password") || !responseData.contains("fingerprint")) {
//             std::cerr << "Неправильна структура відповіді сервера\n";
//             return;
//         }

//         // Отримання даних із відповіді
//         std::string email = responseData["email"];
//         std::string password = responseData["password"];
//         std::string fingerprint = responseData["fingerprint"];

//         // Виклик функції Login для перевірки даних
//         if (this->Login(email, password)) {
//             std::cout << "Користувач авторизований успішно!\n";
//         } else {
//             std::cout << "Невдала спроба входу.\n";
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Помилка: " << e.what() << "\n";
//     }
// }

// // Оновлення токенів
// void Accounts::refreshAccessToken(const std::string& refreshToken) {
//     try {
//         // Формування тіла запиту
//         json requestBody = {
//             {"refresh_token", refreshToken}
//         };

//         // Відправка POST-запиту
//         cpr::Response response = cpr::Post(
//             cpr::Url{"http://localhost:5173/api/auth/refresh-token"},
//             cpr::Body{requestBody.dump()},
//             cpr::Header{{"Content-Type", "application/json"}}
//         );

//         // Перевірка статусу відповіді
//         if (response.status_code == 200) {
//             std::cout << "Токен оновлено успішно!\n";
//         } else {
//             std::cerr << "Помилка оновлення токена: " << response.status_code << "\n";
//             std::cerr << "Відповідь сервера: " << response.text << "\n";
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Помилка: " << e.what() << "\n";
//     }
// }

// // Редагування даних
// void Accounts::renameData(const std::string& name, const std::string& idEditNameDialog) {
//     try {
//         // Формування тіла запиту
//         json requestBody = {
//             {"name", name},
//             {"idEditNameDialog", idEditNameDialog}
//         };

//         // Відправка PUT-запиту
//         cpr::Response response = cpr::Put(
//             cpr::Url{"http://localhost:5173/api/data/rename"},
//             cpr::Body{requestBody.dump()},
//             cpr::Header{{"Content-Type", "application/json"}}
//         );

//         // Перевірка статусу відповіді
//         if (response.status_code == 200) {
//             std::cout << "Дані оновлено успішно!\n";
//         } else {
//             std::cerr << "Помилка оновлення даних: " << response.status_code << "\n";
//             std::cerr << "Відповідь сервера: " << response.text << "\n";
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Помилка: " << e.what() << "\n";
//     }
// }

// // Експорт даних у форматі Excel
// void Accounts::exportExcelData(const std::string& periodDate) {
//     try {
//         // Формування URL із параметром
//         std::string url = "http://localhost:5173/api/export-excel/" + periodDate;

//         // Відправка GET-запиту
//         cpr::Response response = cpr::Get(cpr::Url{url});

//         // Перевірка статусу відповіді
//         if (response.status_code == 200) {
//             std::cout << "Дані успішно експортовано!\n";
//         } else {
//             std::cerr << "Помилка експорту даних: " << response.status_code << "\n";
//             std::cerr << "Відповідь сервера: " << response.text << "\n";
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Помилка: " << e.what() << "\n";
//     }
// }