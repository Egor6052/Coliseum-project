#include <iostream>
#include <string.h>
#include "Logger.h"

class DataCollector : public Logger {
    private:
        std::string data;
        std::string ipAddress;
        std::string nameSensor;
        float current;
        float voltage;
        float activePower;
        float reactivePower;

    public:
        DataCollector();
        ~DataCollector();

        // Protocol
        void RS485();

        // Data
        float roundNumber(float valueNumber);

        // std::string getData();
        std::string getIpAddress();
        std::string getNameSensor();

        float getCurrent();
        float getVoltage();
        float getActivePower();
        float getPowerFactor();
        float getReactivePower();

        void setData(std::string data, std::string ipAddress, std::string nameSensor, float current, float voltage, float activePower, float reactivePower);

        void dataCollector();
        void processData();
        void sendDataToServer();

        std::string getDateTime();
};
