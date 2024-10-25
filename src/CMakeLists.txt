cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Start LANGUAGES CXX)

option(STATUS "OS: ${CMAKE_SYSTEM_NAME}")

# Add the path to the library nlohmann/json
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/nlohmann)

# Searchign package nlohmann_json
find_package(nlohmann_json 3.2.0 REQUIRED)

# Create an executable file
add_executable(start main.cpp 
    dao/entity/SensorData.cpp 
    dao/repository/SensorDataRepository.cpp
    service/ISendData.cpp
    service/implementation/DefaultSendData.cpp
)

# Linking the nlohmann_json library to the project
target_link_libraries(start PRIVATE nlohmann_json::nlohmann_json)
