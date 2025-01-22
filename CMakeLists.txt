cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Назва проекту
project(HTTP_Server)

# Опція для використання статичних бібліотек
option(USE_STATIC "Use static library" ON)

# Вивід повідомлення про систему
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")

# Шлях до вихідних файлів
set(SOURCE_FILES
    ./src/User/CreatePostgresUser.cpp
    ./src/User/UserDB.cpp
    
    ./src/Server/Server.cpp

    ./src/DB/Database.cpp
    ./src/DB/DateTime.cpp
    ./src/DB/CreateTable.cpp
    ./src/DB/CreateBackup.cpp

    ./src/dao/entity/ActivePower.cpp
    ./src/dao/entity/Current.cpp
    ./src/dao/entity/IpAddress.cpp
    ./src/dao/entity/NameSensor.cpp
    ./src/dao/entity/PowerFactor.cpp
    ./src/dao/entity/ReactivePower.cpp
    ./src/dao/entity/Voltage.cpp
    
    ./src/dao/entity/roundNumber.cpp
)

# Заголовкові файли
set(HEADER_FILES
    ./lib/Database.h
    ./lib/Server.h
    ./lib/UserDB.h
)

# Додавання виконуваного файлу
add_executable(start
    src/main.cpp
    ${SOURCE_FILES}
)

# Компіляторні опції
target_compile_options(start
    PRIVATE
        -Wall -fPIC
)

# Додавання шляхів до заголовкових файлів
target_include_directories(start
    PRIVATE
        ./lib
)

find_package(PostgreSQL REQUIRED)
target_link_libraries(start PRIVATE pqxx)
