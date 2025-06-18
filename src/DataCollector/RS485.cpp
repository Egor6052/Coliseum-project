#include <iostream>
// #include <QSerialPort>
// #include <QByteArray>
#include <nlohmann/json.hpp>
// #include <openssl/aes.h>
#include "../headers/DataCollector.h"

    // AES_KEY aesDecryptKey;
    // unsigned char aesKey[16] = { /* 16 байт ключа AES-128 */ };

// Функція для відправлення запиту і отримання даних через RS485
std::string RS485() {

//     QSerialPort serial;

//     // Налаштування послідовного порту RS-485
//     // порт вказано для тестування
//     serial.setPortName("/dev/ttyUSB0");
//     serial.setBaudRate(QSerialPort::Baud9600);
//     serial.setDataBits(QSerialPort::Data8);
//     serial.setParity(QSerialPort::NoParity);
//     serial.setStopBits(QSerialPort::OneStop);
//     serial.setFlowControl(QSerialPort::NoFlowControl);

//     if (!serial.open(QIODevice::ReadWrite)) {
//         qWarning("Не вдалося відкрити послідовний порт");
//         return "{}";  // повертаємо порожній JSON
//     }

//     // Ініціалізація AES-дешифрування
//     AES_set_decrypt_key(aesKey, 128, &aesDecryptKey);

//     QByteArray encryptedData;

//     // Читаємо дані з порту (таймаут 100 мс)
//     while (serial.waitForReadyRead(100)) {
//         encryptedData.append(serial.readAll());
//     }

//     if (encryptedData.isEmpty()) {
//         return "{}";
//     }

//     QByteArray decryptedData;
//     // Розшифровка AES-128 ECB блоками по 16 байт
//     for (int i = 0; i < encryptedData.size(); i += AES_BLOCK_SIZE) {
//         unsigned char decryptedBlock[AES_BLOCK_SIZE];
//         AES_decrypt(reinterpret_cast<const unsigned char*>(encryptedData.constData() + i), decryptedBlock, &aesDecryptKey);
//         decryptedData.append(reinterpret_cast<char*>(decryptedBlock), AES_BLOCK_SIZE);
//     }

//     try {
//         auto parsedJson = json::parse(std::string(decryptedData.constData(), decryptedData.size()));
//         // повертаємо JSON у вигляді рядка
//         return parsedJson.dump();
//     } catch (const json::parse_error& e) {
//         qWarning("Помилка парсингу JSON: %s", e.what());
//         return "{}";
//     }
// }



    return R"({
        "address": "01",
        "command": "10",
        "voltage": 230.5,
        "current": 15.2,
        "activePower": 3500.8,
        "reactivePower": 1200.4,
        "sensorName": "SensorA",
        "ipAddress": "192.168.1.100"
    })";
}