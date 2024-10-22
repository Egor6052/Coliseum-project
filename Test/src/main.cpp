#include "crow/include/crow.h"
// #include "crow/include/crow/settings.h"
// #include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}