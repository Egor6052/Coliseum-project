#include <iostream>
#include <string.h>
#include "Logger.h"

class DataCollector : public Logger {
    private:

    public:
        DataCollector();
        ~DataCollector();

        // Protocol
        std::string RS485(int sensorAddress, int registerAddress, float& result);
        uint16_t calculateCRC(unsigned char* data, int length);

        // Data
        float roundNumber(float valueNumber);

        std::string getIpAddress();
        std::string getNameSensor();
        float getCurrent();
        float getVoltage();
        float getActivePower();
        float getReactivePower();

        std::string dataCollector();
        std::string getDateTime();
};
