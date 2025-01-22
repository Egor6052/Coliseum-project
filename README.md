# Distributed Data Collection System

The distributed data collection system (hereinafter "the System") is designed for automated electricity accounting, consumed by enterprise users, with the capability for remote monitoring and data analysis.

## Features

- **200 independent monitoring channels**: Each channel monitors current, voltage, active/reactive power, and network frequency.
- **Real-time data registration**: Continuously collects and stores data for each channel.
- **Consumption tracking**: Track electricity usage for each client with correlations to main measurement devices.
- **Cable loss accounting**: Automatically factor in cable losses for more accurate reporting.
- **Data visualization**: Graphs and charts for easy analysis of collected data.
- **Automated cost calculation and billing**: Automatically calculate electricity costs and send bills via email or messenger.
- **Data export**: Export data in Excel and 1C formats for further processing.
- **Custom client identification**: Assign unique, editable names to each client.

## System Architecture

- **Protocol**: RS485 with wireless network support.
- **Server Architecture**: Client-server model with a central database for data storage.
- **Database**: SQL database for storing and managing collected data.
- **Operating Systems**: Compatible with Linux and Windows.


## API
```
http://localhost:8080/api/data
```
## Compilation from folder src

To compile the project:
```
g++ -o ./src/build/Start ./src/main.cpp
```

Run the program:
```
../build/Start
```
## Compilation using CMake build system

Configuration:
```
cmake 
```
Compile the binary:
```
cmake build
```
Clear build folder:
```
rm -r ./src/build/*
```
Run App:
```
cd ./src/build && cmake ..
```
```
cmake --build .
```
Start:
```
make
```
```
./start
```
## For develoders

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
1) git checkout -b NEW_BRANCH_NAME
2) git add .
3) git commit -am "COMMENT FOR COMMIT"
4) git push origin NEW_BRANCH_NAME 

## Update your project localy
1) git pull origin NewSite




## Libraries
For JSON format:
if Fedora dnf
```
sudo dnf install nlohmann-json-devel
```
else Debian apt
```
sudo apt install nlohmann-json-devel
```
For PostrgeSQL:
```
sudo apt install postgresql postgresql-contrib
```
And lib for him:
```
sudo apt install libpqxx-dev
```