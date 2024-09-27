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

## Compilation

To compile the project:
```
g++ -o Start ./*.cpp
```

Run the program:
```
./Start
```
##New comit test from DENIS on new branch "denis"