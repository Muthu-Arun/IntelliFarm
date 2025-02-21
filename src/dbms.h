#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include "xdevapi.h"
struct user{
    int id;
    char user_name[128], password[128], name[200];

};
struct sensor_value{
    float val;
    int device_id;
    
};
struct user_devices{
    int user_id;
    char Name[200];

};

class db{
private:
    std::unique_ptr<mysqlx::Session> session;
    std::unique_ptr<mysqlx::Schema> schema;
    
public:
    void insert_new_user(std::unique_ptr<user> user_data);
    void insert_sensor_data(std::unique_ptr<sensor_value> sensor_data);
    void add_device(std::unique_ptr<user_devices> new_device);
    void init();


};
