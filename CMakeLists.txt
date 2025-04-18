cmake_minimum_required(VERSION 3.10)
project(HTTP_Server)

option(USE_STATIC "Use static library" ON)

message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Шлях до вихідних файлів
set(SOURCE_FILES
    # Accounts
    src/Accounts/GenerateUID.cpp
    src/Accounts/Accounts.cpp
    src/Accounts/GetAllUsers.cpp
    src/Accounts/RegisterNewUser.cpp
    src/Accounts/IsAdministrator.cpp
    src/Accounts/Login.cpp
    src/Accounts/GetUserData.cpp

    # Daemon
    src/Daemon/Daemon.cpp
    src/Daemon/addToStartup.cpp
    src/Daemon/removeFromAutostart.cpp

    # User
    src/User/UserDB.cpp

    # Server
    src/Server/Configuration.cpp
    src/Server/Server.cpp
    src/Server/httpServer.cpp

    # Database
    src/DB/CreateBackup.cpp
    src/DB/CreateTable.cpp
    src/DB/Database.cpp
    src/DB/dataCollector.cpp
    src/DB/DateTime.cpp
    src/DB/DeleteData.cpp
    src/DB/GetAllUsers.cpp
    src/DB/GetData.cpp

    # Entity
    src/dao/entity/ActivePower.cpp
    src/dao/entity/Current.cpp
    src/dao/entity/IpAddress.cpp
    src/dao/entity/NameSensor.cpp
    src/dao/entity/PowerFactor.cpp
    src/dao/entity/ReactivePower.cpp
    src/dao/entity/Voltage.cpp
    src/dao/entity/roundNumber.cpp

    # Logger
    src/Logger/DataTime.cpp
    src/Logger/logError.cpp
    src/Logger/Logger.cpp

    # main
    src/main.cpp
)

# Заголовкові файли
set(HEADER_FILES
    src/headers/Accounts.h
    src/headers/Database.h
    src/headers/Daemon.h
    src/headers/Server.h
    src/headers/UserDB.h
    src/headers/Logger.h
)

add_executable(start ${SOURCE_FILES} ${HEADER_FILES})
target_compile_features(start PRIVATE cxx_std_17)

target_compile_options(start PRIVATE -Wall -fPIC)

target_include_directories(start PRIVATE
    ./lib
)

# ============ MariaDB ================
# Пошук MariaDB залежно від платформи
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Detected macOS, using Homebrew paths for MariaDB")

    # Виправлений шлях до MariaDB (для Intel Macs або Rosetta)
    set(MARIADB_ROOT "/usr/local/opt/mariadb-connector-c")

    set(MARIADB_LIBRARY "${MARIADB_ROOT}/lib/libmariadb.dylib")
    set(MARIADB_INCLUDE_DIR "${MARIADB_ROOT}/include/mariadb")

    # Перевіряємо наявність файлів
    if (NOT EXISTS ${MARIADB_LIBRARY})
        message(FATAL_ERROR "MariaDB library not found at ${MARIADB_LIBRARY}")
    endif()

    if (NOT EXISTS ${MARIADB_INCLUDE_DIR}/mysql.h)
        message(FATAL_ERROR "MariaDB headers not found at ${MARIADB_INCLUDE_DIR}/mysql.h")
    endif()

else()
    message(STATUS "Detected Linux or other system, using standard paths for MariaDB")

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
endif()

target_include_directories(start PRIVATE ${MARIADB_INCLUDE_DIR})
target_link_libraries(start PRIVATE ${MARIADB_LIBRARY})

# ============ jsoncpp ================
find_library(JSONCPP_LIBRARY
    NAMES jsoncpp
    PATHS /usr/lib /usr/local/lib /opt/homebrew/lib
)

find_path(JSONCPP_INCLUDE_DIR
    NAMES json/json.h
    PATHS /usr/include /usr/local/include /opt/homebrew/include
          /usr/include/json /usr/local/include/json /opt/homebrew/include/json
)

if (NOT JSONCPP_LIBRARY OR NOT JSONCPP_INCLUDE_DIR)
    message(WARNING "jsoncpp library or headers not found. Will try to proceed anyway.")
else()
    target_include_directories(start PRIVATE ${JSONCPP_INCLUDE_DIR})
    target_link_libraries(start PRIVATE ${JSONCPP_LIBRARY})
endif()

# ============ nlohmann/json (header-only) ============
target_include_directories(start PRIVATE lib/json)

# find_path(NLOHMANN_JSON_DIR
#     NAMES nlohmann/json.hpp
#     PATHS /usr/include /usr/local/include /opt/homebrew/include
# )

# if (NLOHMANN_JSON_DIR)
#     target_include_directories(start PRIVATE ${NLOHMANN_JSON_DIR})
# else()
#     message(WARNING "nlohmann/json.hpp not found. Make sure it's available or install with 'brew install nlohmann-json'")
# endif()

# ============ OS-Specific libraries ============
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(start PRIVATE
        z
        ssl
        crypto
        dl
        pthread
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS doesn't need dl/pthread/ssl in більшість випадків, але можна перевіряти тут
    find_library(SECURITY_FRAMEWORK Security)
    if (SECURITY_FRAMEWORK)
        target_link_libraries(start PRIVATE ${SECURITY_FRAMEWORK})
    endif()
endif()
