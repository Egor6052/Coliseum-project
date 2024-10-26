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

		void saveData(float currentValue, float voltageValue, float activePower, float reactivePower, std::string& nameValue);
		
		//To json
		nlohmann::json toJson() const;

		// TODO path to load db
		// Repository repository;
		// repository.saveToJsonFile("..../database/sensor_data.json");

		bool saveToJsonFile(const std::string& filePath) const;
};

#endif
