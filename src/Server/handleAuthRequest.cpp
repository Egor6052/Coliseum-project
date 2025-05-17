#include <iostream>
#include <thread>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/Accounts.h"
#include "../../lib/http/httplib.h"
#include <json/json.h>
class Permission {
    private:
        int id;
        std::string name;
    
    public:
        Permission(int id, std::string name) : id(id), name(name) {}
        
        int getId() const { return id; }
        std::string getName() const { return name; }
    };
    
    class Role {
    private:
        int id;
        std::string name;
        std::vector<Permission> permissions;
    
    public:
        Role(int id, std::string name, std::vector<Permission> permissions) 
            : id(id), name(name), permissions(permissions) {}
        
        int getId() const { return id; }
        std::string getName() const { return name; }
        std::vector<Permission> getPermissions() const { return permissions; }
    };


// Обробка JSON-запиту для автентифікації
void Server::handleAuthRequest(const httplib::Request &req, httplib::Response &res, const std::string &endpoint) {
    std::cout << "Отримано POST-запит до " << endpoint << ": " << req.body << std::endl;
    Json::Value json;
    Json::Reader reader;
    Json::Value data;

    if (reader.parse(req.body, data)) {
        std::string email = data["email"].asString();
        std::string password = data["password"].asString();
        std::string fingerPrint = data["fingerPrint"].asString();
        std::cout << "Email: " << email << "\nPassword: " << password << "\nFingerPrint: " << fingerPrint << std::endl;

        // Перевірка логіна та пароля
        Accounts account;
        if (account.Login(email, password)) {
            // Формуємо успішну відповідь
            Json::Value response;
            
            // Зберігаємо токени в БД
            std::string accessToken = account.generateAccessToken(email, getKeyAccess());
            std::string refreshToken = account.generateRefreshToken(email, getKeyRefresh());
            
            // Метод для збереження токенів в БД
            // account.storeTokens(email, accessToken, refreshToken);
            
            response["accessToken"] = accessToken;
            response["refreshToken"] = refreshToken;
            
            // Дані користувача
            response["user"]["id"] = account.getUID();
            response["user"]["userName"] = account.getUserName(account.getUID());
            response["user"]["email"] = email;
            
            // Створюємо масив ролей замість рядка
            Json::Value rolesArray(Json::arrayValue);
            
            // Припустимо, у нас є рядок з ролями, який ми розбиваємо і формуємо масив
            std::string rolesString = account.getUserRole(account.getUID());
            
            // Видаляємо символи '[', ']' та подвійні кавички з рядка ролей
            rolesString.erase(std::remove(rolesString.begin(), rolesString.end(), '['), rolesString.end());
            rolesString.erase(std::remove(rolesString.begin(), rolesString.end(), ']'), rolesString.end());
            rolesString.erase(std::remove(rolesString.begin(), rolesString.end(), '"'), rolesString.end());
            
            // Розбиваємо рядок на окремі ролі за комою
            std::vector<std::string> roleNames;
            std::stringstream ss(rolesString);
            std::string roleName;
            while (std::getline(ss, roleName, ',')) {
              // Видаляємо зайві пробіли
                roleName.erase(0, roleName.find_first_not_of(" \t\n\r\f\v"));
                roleName.erase(roleName.find_last_not_of(" \t\n\r\f\v") + 1);
                
                if (!roleName.empty()) {
                    roleNames.push_back(roleName);
                }
            }
            
            // Створюємо об'єкти ролей та додаємо їх у масив
            int roleId = 1;
            for (const auto& roleName : roleNames) {
            Json::Value roleObj;
            roleObj["Id"] = roleId++;
            roleObj["Name"] = roleName;
            
            // Створюємо масив дозволів для кожної ролі
            Json::Value permissionsArray(Json::arrayValue);
            
            // Для прикладу додаємо деякі дозволи залежно від ролі
            if (roleName == "user") {
                Json::Value readPermission;
                readPermission["Id"] = 1;
                readPermission["Name"] = "read";
                permissionsArray.append(readPermission);
                
                Json::Value writePermission;
                writePermission["Id"] = 2;
                writePermission["Name"] = "write";
                permissionsArray.append(writePermission);
            } 
            else if (roleName == "admin") {
                Json::Value readPermission;
                readPermission["Id"] = 1;
                readPermission["Name"] = "read";
                permissionsArray.append(readPermission);
                
                Json::Value writePermission;
                writePermission["Id"] = 2;
                writePermission["Name"] = "write";
                permissionsArray.append(writePermission);
                
                Json::Value deletePermission;
                deletePermission["Id"] = 3;
                deletePermission["Name"] = "delete";
                permissionsArray.append(deletePermission);
                
                Json::Value adminPermission;
                adminPermission["Id"] = 4;
                adminPermission["Name"] = "admin";
                permissionsArray.append(adminPermission);
                }
                
                roleObj["Permissions"] = permissionsArray;
                rolesArray.append(roleObj);
            }
            
            response["user"]["roles"] = rolesArray;
            
            Json::StreamWriterBuilder writer;
            std::string responseStr = Json::writeString(writer, response);
            
            std::cout << "Response: " << responseStr << std::endl;
            res.set_header("Authorization", "Bearer " + response["accessToken"].asString());
            res.set_content(responseStr, "application/json");
        }

    } else {
        Json::Value errorResponse;
        errorResponse["error"] = "Invalid JSON";
        Json::StreamWriterBuilder writer;
        std::string errorResponseStr = Json::writeString(writer, errorResponse);
        std::cout << "Error Response: " << errorResponseStr << std::endl;
        res.status = 400; // Bad Request
        res.set_content(errorResponseStr, "application/json");
    }
}


