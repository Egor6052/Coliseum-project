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
    ./src/Accounts/GenerateUID.cpp
    ./src/Accounts/Accounts.cpp
    ./src/Accounts/GetAllAdmins.cpp
    ./src/Accounts/GetAllUsers.cpp
    ./src/Accounts/RegisterAsAdmin.cpp
    ./src/Accounts/RegisterAsUser.cpp
    ./src/Accounts/SetEmail.cpp
    ./src/Accounts/SetPhoneNumber.cpp
    # ./src/Accounts/RegisterUser.cpp
    ./src/Accounts/IsAdministrator.cpp
    ./src/Accounts/Login.cpp
    ./src/Accounts/GetUserData.cpp

    ./src/Daemon/Daemon.cpp
    ./src/Daemon/addToStartup.cpp
    ./src/Daemon/backgroundMode.cpp
    ./src/Daemon/removeFromAutostart.cpp

    # ./src/User/createMySQLUser.cpp
    ./src/User/UserDB.cpp
    ./src/Server/Server.cpp

    ./src/DB/Database.cpp
    ./src/DB/DateTime.cpp
    ./src/DB/CreateTable.cpp
    ./src/DB/CreateBackup.cpp
    ./src/DB/GetData.cpp
    ./src/DB/DeleteData.cpp


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
    ./lib/Accounts.h
    ./lib/Database.h
    ./lib/Daemon.h
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
        /usr/include/mysql
)

# Вказуємо шлях до бібліотеки mysqlclient
# link_directories(/usr/lib64/mysql)

find_library(MYSQL_LIB mysqlclient HINTS /usr/lib64/mysql)
target_link_libraries(start PRIVATE ${MYSQL_LIB})

# Підключаємо бібліотеку mysqlclient для лінкування
# target_link_libraries(start PRIVATE mysqlclient)
# find_library(MYSQL_LIB mysqlclient HINTS /usr/lib64/mysql)
# target_link_libraries(start PRIVATE ${MYSQL_LIB})



# Лінкування з бібліотеками MySQL
# find_package(MySQL REQUIRED)
# target_link_libraries(start PRIVATE ${MYSQL_LIBRARIES})

