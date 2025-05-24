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
    src/Accounts/getUserEmail.cpp
    src/Accounts/getUserName.cpp
    src/Accounts/GetUserRole.cpp
    src/Accounts/getUserPassword.cpp
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
find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(MARIADB QUIET libmariadb)
endif()

if (MARIADB_FOUND)
    message(STATUS "MariaDB found via pkg-config: ${MARIADB_LIBRARIES}")
    target_include_directories(start PRIVATE ${MARIADB_INCLUDE_DIRS})
    target_link_libraries(start PRIVATE ${MARIADB_LIBRARIES})
else()
    find_library(MARIADB_LIBRARY
        NAMES mariadbclient mariadb libmariadb
        PATHS
            /usr/lib
            /usr/lib64
            /usr/local/lib
            /opt/homebrew/lib
            /usr/local/Cellar/mariadb-connector-c/*/lib
    )
    find_path(MARIADB_INCLUDE_DIR
        NAMES mysql.h
        PATHS
            /usr/include
            /usr/include/mariadb
            /usr/local/include
            /usr/local/include/mariadb
            /opt/homebrew/include
            /opt/homebrew/include/mariadb
            /usr/local/Cellar/mariadb-connector-c/*/include
    )

    if (NOT MARIADB_LIBRARY OR NOT MARIADB_INCLUDE_DIR)
        message(FATAL_ERROR "MariaDB library or headers not found. Please ensure MariaDB Connector/C is installed (e.g., `sudo apt-get install libmariadb-dev` on Ubuntu or `brew install mariadb-connector-c` on macOS).")
    endif()
    message(STATUS "MariaDB found: ${MARIADB_LIBRARY}, ${MARIADB_INCLUDE_DIR}")
    target_include_directories(start PRIVATE ${MARIADB_INCLUDE_DIR})
    target_link_libraries(start PRIVATE ${MARIADB_LIBRARY})
endif()

# ============ zlib ============
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    message(STATUS "zlib found: ${ZLIB_LIBRARIES}")
    target_include_directories(start PRIVATE ${ZLIB_INCLUDE_DIRS})
    target_link_libraries(start PRIVATE ${ZLIB_LIBRARIES})
else()
    message(FATAL_ERROR "zlib library not found. Please ensure zlib is installed (e.g., `sudo apt-get install zlib1g-dev` on Ubuntu or `brew install zlib` on macOS).")
endif()

# ============ nlohmann/json ============
find_path(NLOHMANN_JSON_INCLUDE_DIR
    NAMES nlohmann/json.hpp
    PATHS
        ${CMAKE_SOURCE_DIR}/lib/json
    NO_DEFAULT_PATH
)

if (NOT NLOHMANN_JSON_INCLUDE_DIR)
    message(FATAL_ERROR "nlohmann/json headers not found in ${CMAKE_SOURCE_DIR}/lib/json. Please ensure nlohmann/json.hpp is placed in lib/json/nlohmann/.")
endif()
message(STATUS "nlohmann/json found: ${NLOHMANN_JSON_INCLUDE_DIR}")
target_include_directories(start PRIVATE ${NLOHMANN_JSON_INCLUDE_DIR})


# ============ libmodbus ============
find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(LIBMODBUS QUIET libmodbus)
endif()

if (LIBMODBUS_FOUND)
    message(STATUS "libmodbus found via pkg-config: ${LIBMODBUS_LIBRARIES}")
    target_include_directories(start PRIVATE ${LIBMODBUS_INCLUDE_DIRS})
    target_link_libraries(start PRIVATE ${LIBMODBUS_LIBRARIES})
else()
    find_library(LIBMODBUS_LIBRARY
        NAMES modbus libmodbus
        PATHS
            /usr/lib
            /usr/lib64
            /usr/local/lib
            /opt/homebrew/lib
            /usr/local/Cellar/libmodbus/*/lib
    )
    find_path(LIBMODBUS_INCLUDE_DIR
        NAMES modbus/modbus.h
        PATHS
            /usr/include
            /usr/local/include
            /opt/homebrew/include
            /usr/local/Cellar/libmodbus/*/include
    )

    if (NOT LIBMODBUS_LIBRARY OR NOT LIBMODBUS_INCLUDE_DIR)
        message(FATAL_ERROR "libmodbus library or headers not found. Please ensure libmodbus is installed (e.g., `sudo apt-get install libmodbus-dev` on Ubuntu or `brew install libmodbus` on macOS).")
    endif()
    message(STATUS "libmodbus found: ${LIBMODBUS_LIBRARY}, ${LIBMODBUS_INCLUDE_DIR}")
    target_include_directories(start PRIVATE ${LIBMODBUS_INCLUDE_DIR})
    target_link_libraries(start PRIVATE ${LIBMODBUS_LIBRARY})
endif()


# ============ OS-specific libraries ============
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(start PRIVATE
        dl
        pthread
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_library(SECURITY_FRAMEWORK Security)
    if (SECURITY_FRAMEWORK)
        target_link_libraries(start PRIVATE ${SECURITY_FRAMEWORK})
    endif()
endif()