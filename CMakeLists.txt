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
    # Accounts
    ./src/Accounts/GenerateUID.cpp
    ./src/Accounts/Accounts.cpp
    ./src/Accounts/GetAllUsers.cpp
    ./src/Accounts/RegisterNewUser.cpp
    ./src/Accounts/IsAdministrator.cpp
    ./src/Accounts/Login.cpp
    ./src/Accounts/GetUserData.cpp

    # Daemon
    ./src/Daemon/Daemon.cpp
    ./src/Daemon/addToStartup.cpp
    ./src/Daemon/removeFromAutostart.cpp

    # User
    ./src/User/UserDB.cpp

    # Server
    # ./src/Server/readFile.cpp
    # ./src/Server/getCommonHeader.cpp
    # ./src/Server/getCommonFooter.cpp
    ./src/Server/Configuration.cpp
    ./src/Server/Server.cpp
    ./src/Server/httpServer.cpp

    # Database
    ./src/DB/CreateBackup.cpp
    ./src/DB/CreateTable.cpp
    ./src/DB/Database.cpp
    ./src/DB/dataCollector.cpp
    ./src/DB/DateTime.cpp
    ./src/DB/DeleteData.cpp
    ./src/DB/GetAllUsers.cpp
    ./src/DB/GetData.cpp

    # entity
    ./src/dao/entity/ActivePower.cpp
    ./src/dao/entity/Current.cpp
    ./src/dao/entity/IpAddress.cpp
    ./src/dao/entity/NameSensor.cpp
    ./src/dao/entity/PowerFactor.cpp
    ./src/dao/entity/ReactivePower.cpp
    ./src/dao/entity/Voltage.cpp
    ./src/dao/entity/roundNumber.cpp

    # Logger
    ./src/Logger/DataTime.cpp
    ./src/Logger/logError.cpp
    ./src/Logger/Logger.cpp
)

# Заголовкові файли
set(HEADER_FILES
    ./lib/Accounts.h
    ./lib/Database.h
    ./lib/Daemon.h
    ./lib/Server.h
    ./lib/UserDB.h
    ./lib/Logger.h
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

# Додаємо include-директорії
target_include_directories(start PRIVATE
    ./lib
)

# Знаходимо бібліотеку MariaDB
find_library(MARIADB_LIBRARY
    NAMES mariadb mariadbclient
    PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64
)

find_path(MARIADB_INCLUDE_DIR
    NAMES mysql.h
    PATHS /usr/include /usr/include/mysql /usr/local/include /usr/local/include/mysql
)

if (NOT MARIADB_LIBRARY OR NOT MARIADB_INCLUDE_DIR)
    message(FATAL_ERROR "MariaDB library or headers not found. Please install MariaDB development package.")
endif()

# Додаємо include-директорію для MariaDB
target_include_directories(start PRIVATE ${MARIADB_INCLUDE_DIR})

# Знаходимо бібліотеку jsoncpp
find_library(JSONCPP_LIBRARY
    NAMES jsoncpp
    PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64
)

find_path(JSONCPP_INCLUDE_DIR
    NAMES json/json.h
    PATHS /usr/include /usr/include/json /usr/local/include /usr/local/include/json
)

if (NOT JSONCPP_LIBRARY OR NOT JSONCPP_INCLUDE_DIR)
    message(FATAL_ERROR "jsoncpp library or headers not found. Please install jsoncpp development package.")
endif()

# Додаємо include-директорію для jsoncpp
target_include_directories(start PRIVATE ${JSONCPP_INCLUDE_DIR})

# Лінкуємо бібліотеки
target_link_libraries(start PRIVATE
    ${MARIADB_LIBRARY}
    ${JSONCPP_LIBRARY}
    z  # Для zlib
    ssl  # Для OpenSSL
    crypto  # Для OpenSSL
    dl  # Для динамічного завантаження (на Linux)
    pthread  # Для потоків
)