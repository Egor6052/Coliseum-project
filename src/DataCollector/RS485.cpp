#include <iostream>
#include <iomanip>
#include <sstream>
#include <modbus/modbus.h>
#include "../headers/DataCollector.h"

// Функція для відправлення запиту і отримання даних через RS485
std::string DataCollector::RS485(int sensorAddress, int registerAddress, float& result) {
    // modbus_t* ctx = nullptr;
    // const char* port = "/dev/ttyUSB0";
    // std::stringstream ss;

    // // Створюємо контекст для Modbus RTU
    // ctx = modbus_new_rtu(port, 9600, 'N', 8, 1);
    // if (ctx == nullptr) {
    //     std::cerr << "Помилка створення контексту Modbus!\n";
    //     return "Error: Failed to create Modbus context";
    // }

    // // Встановлюємо адресу датчика
    // if (modbus_set_slave(ctx, sensorAddress) < 0) {
    //     std::cerr << "Помилка встановлення адреси датчика!\n";
    //     modbus_free(ctx);
    //     return "Error: Failed to set slave address";
    // }

    // // Підключаємося до порту
    // if (modbus_connect(ctx) < 0) {
    //     std::cerr << "Помилка підключення до порту!\n";
    //     modbus_free(ctx);
    //     return "Error: Failed to connect to port";
    // }

    // // Читання регістрів (2 регістри для float)
    // uint16_t registers[2];
    // int rc = modbus_read_registers(ctx, registerAddress, 2, registers);
    // if (rc != 2) {
    //     std::cerr << "Помилка читання регістрів!\n";
    //     modbus_free(ctx);
    //     return "Error: Failed to read registers";
    // }

    // // Конвертація регістрів у float
    // uint32_t raw_value = (registers[0] << 16) | registers[1];
    // memcpy(&result, &raw_value, sizeof(float));

    // // Формуємо рядок відповіді (шістнадцяткове представлення регістрів)
    // ss << std::hex << std::setfill('0');
    // for (int i = 0; i < 2; ++i) {
    //     ss << std::setw(4) << registers[i];
    //     if (i < 1) ss << " ";
    // }

    // // Закриваємо з’єднання
    // modbus_close(ctx);
    // modbus_free(ctx);

    // return ss.str();
    return "Error: RS485 function is not implemented";
}