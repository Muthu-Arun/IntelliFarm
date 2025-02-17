#pragma once
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <memory>
#include <cppconn/exception.h>


struct weatherData{
    float temp, pressure, humidity;
    std::string location;
    unsigned long source_id;
};
class ram_cache{
public:
    static weatherData* wdata;
    static void initialize();
};
namespace db {
    void init();

}
    
