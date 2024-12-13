#pragma once
#include<sqlite3.h>
#include <iostream>

namespace db{
struct userData{

    unsigned long id;
    std::string name;
    

};
struct weatherData{
    float temp, pressure, humidity;
    std::string location;
    unsigned long source_id;
};
extern sqlite3* db;
extern char* errmsg;
extern int err;
void insert(const userData&);
void get(weatherData&);
void put(const weatherData&);
void initialize();
}

namespace ram_cache{
extern db::weatherData* wdata;
void initialize();
void update(const db::weatherData&);
void get(db::weatherData&);
}
