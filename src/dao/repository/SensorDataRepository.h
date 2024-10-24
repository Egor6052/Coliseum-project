#pragma once
#ifndef SENSORDATAREPOSITORY_H
#define SENSORDATAREPOSITORY_H

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

class Repository {
	private:
		static int count;
    	int id;

		float current;
		float voltage;

		float activePower;
    	float reactivePower;

		std::string nameSensor;
	public:
		Repository();

		void setData(float currentValue, float voltageValue, float activePower, float reactivePower, std::string& nameValue);
		
		void setName(std::string nameValue);
		//Get parameters
		float getCurrent();
		float getVoltage();
		std::string getNameSensor();
		int getID();

		//To json
		nlohmann::json toJson() const;
};

#endif