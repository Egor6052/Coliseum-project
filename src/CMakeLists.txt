cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Start LANGUAGES CXX)

# Вказуємо шлях до локальної папки з бібліотеками
set(LOCAL_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Додаємо JSON-бібліотеку nlohmann
include_directories(${LOCAL_LIB_PATH}/nlohmann)

# Шукаємо nlohmann_json
find_package(nlohmann_json REQUIRED)

# Включаємо Boost з локальної папки
set(BOOST_ROOT ${LOCAL_LIB_PATH}/boost) # Шлях до папки з Boost
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include) # Директорія заголовків
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib) # Директорія бібліотек

# Шукаємо Boost компоненти
find_package(Boost REQUIRED COMPONENTS system thread)

# Додаємо pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Create an executable file
add_executable(start main.cpp 
    ./server/*.cpp
    # dao/entity/SensorData.cpp 
    # dao/repository/SensorDataRepository.cpp
    # service/ISendData.cpp
    # service/implementation/DefaultSendData.cpp
)

# Лінкуємо Boost до проєкту
target_link_libraries(start PRIVATE Boost::system Boost::thread)

# Лінкуємо бібліотеку nlohmann_json до проєкту
target_link_libraries(start PRIVATE nlohmann_json::nlohmann_json)
