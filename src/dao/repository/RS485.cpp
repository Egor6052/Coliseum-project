#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "../../headers/Server.h"

void Server::RS485(){
// TODO
    const char* port = "/dev/ttyUSB0";

    int serial_port = open(port, O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        std::cerr << "Помилка відкриття порту!\n";
        // return 1;
    }

    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "Помилка отримання налаштувань порту!\n";
        // return 1;
    }

    // Налаштування порту
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag = CS8 | CLOCAL | CREAD;

    tcsetattr(serial_port, TCSANOW, &tty);

    // Читання даних
    char buffer[256];
    int n = read(serial_port, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        std::cout << "Отримано: " << buffer << std::endl;
    }

    close(serial_port);
    
    // return 0;
}
