Interface for simplified installation, creation and configuration of a database with PostgreSQL.

Install libraries: 
```
sudo apt-get install libpqxx-dev
```
Build in main folder: 
```
g++ -o ../build/Start ./*.cpp -lpqxx -lpq
```
Start: 
```
./Start
```