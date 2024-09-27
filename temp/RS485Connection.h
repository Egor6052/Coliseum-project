#pragma once
#ifndef RS485CONNECTION_H
#define RS485CONNECTION_H

#include <iostream>
#include <string>

class RS485Connection {
private:
    std::string port;       // Порт для підключення
    int baudRate;           // Швидкість передачі даних
    int timeout;            // Таймаут для з'єднання

public:
    RS485Connection(const std::string& port, int baudRate, int timeout);
    
    bool connect();         // Метод для з'єднання
    std::string receive();  // Метод для отримання даних від датчика
    bool send(const std::string& data);  // Відправка даних (якщо потрібно)
    void close();           // Закриття з'єднання
};

#endif