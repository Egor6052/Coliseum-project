## Distributed Data Collection System
---
The distributed data collection system (hereinafter "the System") is designed for automated electricity accounting, consumed by enterprise users, with the capability for remote monitoring and data analysis.

---
**_Content:_**
- [Distributed Data Collection System](#distributed-data-collection-system)
- [Features](#features)
  - [System Architecture](#system-architecture)
- [API](#api)
- [Compiling](#compiling)
- [Daemon Management](#daemon-management)
  - [Start server:](#start-server)
- [For develoders](#for-develoders)
- [Ho to push](#ho-to-push)
- [Libraries and extensions](#libraries-and-extensions)
- [Create user for System](#create-user-for-system)
- [Add users to DB](#add-users-to-db)
---

## Features
---
- **200 independent monitoring channels**: Each channel monitors current, voltage, active/reactive power, and network frequency.
- **Real-time data registration**: Continuously collects and stores data for each channel.
- **Consumption tracking**: Track electricity usage for each client with correlations to main measurement devices.
- **Cable loss accounting**: Automatically factor in cable losses for more accurate reporting.
- **Data visualization**: Graphs and charts for easy analysis of collected data.
- **Automated cost calculation and billing**: Automatically calculate electricity costs and send bills via email or messenger.
- **Data export**: Export data in Excel and 1C formats for further processing.
- **Custom client identification**: Assign unique, editable names to each client.

### System Architecture

- **Protocol**: RS485 with wireless network support.
- **Server Architecture**: Client-server model with a central database for data storage.
- **Database**: SQL database for storing and managing collected data.
- **Operating Systems**: Compatible with Linux and Windows.

## API
---
```sh
http://192.168.0.112:5173/client
```
<!-- 5182 -->

## Compiling in the directory ./build
---
Configuration:
```sh
cmake ..
```
Compile the binary:
```sh
cmake --build .
```
Start:
```sh
sudo ./start
```

## Daemon Management
---
Reload Daemons
```sh
sudo systemctl daemon-reload
```

Restart Daemon
```sh
sudo systemctl restart SensorDaemon.service
```

Disable Daemon
```sh
sudo systemctl disable SensorDaemon.service
```

Enable Daemon
```sh
sudo systemctl enable SensorDaemon.service
```

Start daemon
```sh
sudo systemctl start SensorDaemon.service
```

Check Daemon Status
```sh
sudo systemctl status SensorDaemon.service
```

### Start database:
---
```sh
sudo systemctl start mysqld
```
**Add to startup:**
```sh
sudo systemctl enable mysqld
```
**Checking the status:**
```sh
sudo systemctl status mysqld
```

## For develoders
---
1) Structure folders "src/":
-dao:(folder for data and using this data)
--entity (data object ,which will be save on db)
--repository (methods, which modification data in db, example, saveSensorData,getSensorData,... )
-dto(object data without not need property. Example e have User({email:fsdf,passord:31433}) and we convert to UserDTO({email:fsdf}))
-mapper(methods , which convert data from User to UserDTO . name: UserMapper.cpp)
-config(init CONST data)
-service(in this folder ill be save abstract classes or interfaces. name: ISendData.cpp, where I=interface ):
--impl(classes ith realization abstract class . name: DefaultSendData.cpp)

Folder "build": there will saved run .exe or .sh file

Folder "temp": files need distribution 

2) find //TODO for find what to do 


## Libraries and extensions
---
**For JSON format:**
**Debian** apt
```sh
sudo apt install nlohmann-json-devel
```
**Fedora** dnf
```sh
sudo dnf install nlohmann-json-devel
```

**MySQL:**

if **dnf**
```sh
sudo dnf install mysql-server mysql-devel
```
if **apt**
```sh
sudo apt install mysql-server
```

**libmodbus** — this is a cross-platform library for working with the Modbus protocol (RTU і TCP), for RS485
```sh
sudo apt-get install libmodbus-dev
```

**for MacOS**
```sh
brew install libmodbus
brew install mariadb-connector-c
brew install jsoncpp
brew install openssl
```

## Create User for System
Enter to DB as root
```sh
sudo mariadb
```
Create new user and grant all privileges to him:
```sh
CREATE USER 'data_writer'@'%' IDENTIFIED BY 'MySqlStrongPassword123';
GRANT ALL PRIVILEGES ON *.* TO 'data_writer'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EXIT;
```

You can also create a tables for data and users!
Log in to MySQL/MariaDB as a new user:

```sh
mysql -u data_writer -p
```
Enter the password:
```sh
MySqlStrongPassword123
```

Tables can only be created inside a database. 
Create DB firstly:
```sh
CREATE DATABASE IF NOT EXISTS sensor_data;
USE sensor_data;
```

Create table for users in DB:
```sh
CREATE TABLE IF NOT EXISTS users_data_table (
    uid VARCHAR(255) PRIMARY KEY,
    login VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    email VARCHAR(255),
    role ENUM('user', 'admin') NOT NULL DEFAULT 'user'
);
```
Audit:
```sh
SHOW TABLES;
SELECT * FROM users_data_table;
```

Create table SensorData table in DB:
```sh
CREATE TABLE IF NOT EXISTS sensor_data_table (
    id INT AUTO_INCREMENT PRIMARY KEY,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    ip_address VARCHAR(255) NOT NULL,
    sensor_name VARCHAR(255) NOT NULL,
    current FLOAT NOT NULL,
    voltage FLOAT NOT NULL,
    active_power FLOAT NOT NULL,
    reactive_power FLOAT NOT NULL
);
```

Audit:
```sh
SHOW TABLES;
SELECT * FROM sensor_data_table;
```


Restart DB:
```sh
sudo systemctl restart mariadb
```

## Add users to DB

Example of insertion:
```sh
INSERT INTO users_data_table (uid, login, password, email, role)
VALUES 
('u1', 'NameUser1', '12345678', 'user1@gmail.com', 'admin'),
('u2', 'NameUser2', '12345678', 'user2@example.com', 'user');
```

Delete user from DB:
where u1 - UID user, which you wont to delete.
```sh
DELETE FROM users_data_table WHERE uid = 'u1';
```

Delete table:
```sh
DROP TABLE table_name;
```