#include <iostream>
#include "./server/HTTP_server.h"

int main() {
    std::cout << "The distributed data collection system" << std::endl;

    HTTP http1;
    http1.start();

    return 0;
}
