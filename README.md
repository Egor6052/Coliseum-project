## Distributed Data Collection System
---
The distributed data collection system (hereinafter "the System") is designed for automated electricity accounting, consumed by enterprise users, with the capability for remote monitoring and data analysis.

---
**_list:_**
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
http://localhost:8080/
```

## Compiling
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

## Ho to push
--- 

1) git checkout -b NEW_BRANCH_NAME
2) git add .
3) git commit -am "COMMENT FOR COMMIT"
4) git push origin NEW_BRANCH_NAME 

**Update your project localy**
1) git pull origin NewSite


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
