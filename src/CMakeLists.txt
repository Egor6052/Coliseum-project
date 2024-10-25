 
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Start LANGUAGES CXX)

option(STATUS "OS: ${CMAKE_SYSTEM_NAME}")

add_executable(start main.cpp 
	dao/entity/SensorData.cpp 
	dao/repository/SensorDataRepository.cpp
	service/ISendData.cpp
	service/implementation/DefaultSendData.cpp

)