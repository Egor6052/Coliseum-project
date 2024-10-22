Crow - легкий HTTP-сервер для C++:
```
git clone https://github.com/ipkn/crow.git
```
Для бібліотеки nlohmann/json:
```
git clone https://github.com/nlohmann/json.git

dpkg -L nlohmann-json-dev | grep include

```

Компіляція:
```
g++ -std=c++11 -o server main.cpp -I~/Стільниця/Coliseum-project/Test/crow/include -I/path/to/nlohmann/json
```