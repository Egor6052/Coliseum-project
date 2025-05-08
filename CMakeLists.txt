cmake_minimum_required(VERSION 3.10)
project(HTTP_Server)

option(USE_STATIC "Use static library" ON)

message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============ Source Files ============
set(SOURCE_FILES
    # Accounts
    src/Accounts/GenerateUID.cpp
    src/Accounts/Accounts.cpp
    src/Accounts/GetAllUsers.cpp
    src/Accounts/RegisterNewUser.cpp
    src/Accounts/IsAdministrator.cpp
    src/Accounts/Login.cpp
    src/Accounts/GetUserData.cpp
    src/Accounts/GetUserRole.cpp
    src/Accounts/generateTokens.cpp

    # Auth
    src/auth/LoginFromAPI.cpp

    # Daemon
    src/Daemon/Daemon.cpp
    src/Daemon/addToStartup.cpp
    src/Daemon/removeFromAutostart.cpp

    # Server
    src/Server/Configuration.cpp
    src/Server/Server.cpp
    src/Server/httpServer.cpp
    src/Server/handleAuthRequest.cpp
    src/Server/handleClientRoutes.cpp
    src/Server/handleRefreshTokenRequest.cpp
    src/Server/Logout.cpp
    src/Server/setupCORS.cpp
    src/Server/setupStaticFiles.cpp

    # Database
    src/DB/CreateBackup.cpp
    src/DB/CreateTable.cpp
    src/DB/Database.cpp
    src/DB/dataCollector.cpp
    src/DB/DateTime.cpp
    src/DB/DeleteData.cpp
    src/DB/GetAllUsers.cpp
    src/DB/GetData.cpp

    # DataCollector
    src/DataCollector/ActivePower.cpp
    src/DataCollector/Current.cpp
    src/DataCollector/DataCollector.cpp
    src/DataCollector/DateTime.cpp
    src/DataCollector/IpAddress.cpp
    src/DataCollector/NameSensor.cpp
    src/DataCollector/PowerFactor.cpp
    src/DataCollector/ReactivePower.cpp
    src/DataCollector/Voltage.cpp
    src/DataCollector/roundNumber.cpp
    src/DataCollector/RS485.cpp

    # Logger
    src/Logger/DataTime.cpp
    src/Logger/logError.cpp
    src/Logger/Logger.cpp

    # main
    src/main.cpp
)

add_executable(start ${SOURCE_FILES})

# ============ Include Directories ============
target_include_directories(start PRIVATE
    ./lib/jwt-cpp/include
    ./lib
    src/headers
    lib/json
)

# ============ Compiler Options ============
target_compile_features(start PRIVATE cxx_std_17)
target_compile_options(start PRIVATE -Wall -fPIC)

# ============ OpenSSL ============
find_package(OpenSSL REQUIRED)
target_link_libraries(start PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# ============ MariaDB ============
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Detected macOS, using Homebrew paths for MariaDB")
    set(MARIADB_ROOT "/usr/local/opt/mariadb-connector-c")
    find_library(MARIADB_LIBRARY mariadb HINTS "${MARIADB_ROOT}/lib")
    find_path(MARIADB_INCLUDE_DIR mysql.h HINTS "${MARIADB_ROOT}/include/mariadb")
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
endif()

if (NOT MARIADB_LIBRARY OR NOT MARIADB_INCLUDE_DIR)
    message(FATAL_ERROR "MariaDB library or headers not found. Please install MariaDB development package.")
endif()

target_include_directories(start PRIVATE ${MARIADB_INCLUDE_DIR})
target_link_libraries(start PRIVATE ${MARIADB_LIBRARY})

# ============ jsoncpp ============
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

# ============ OS-specific libraries ============
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(start PRIVATE
        z
        ssl
        crypto
        dl
        pthread
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_library(SECURITY_FRAMEWORK Security)
    if (SECURITY_FRAMEWORK)
        target_link_libraries(start PRIVATE ${SECURITY_FRAMEWORK})
    endif()
endif()
