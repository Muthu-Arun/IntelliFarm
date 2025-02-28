#pragma once
#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include "xdevapi.h"
#include <chrono>
#include<vector>
#include<string>
struct user{
    int id;
    char user_name[128], password[128], name[200];
    user(const char* usr_name, const char* password, const char* name){
        strcpy(this->user_name,usr_name);
        strcpy(this->password,password);
        strcpy(this->name,name);
    }
};
struct sensor_value{
    float val;
    int device_id;
    std::time_t timestamp;
    sensor_value(float value,std::time_t ts) : val{value}, timestamp{ts} {}
    sensor_value(float value, int sensor_device_id) : val{value}, device_id{sensor_device_id} {}
    
};
struct user_devices{
    int user_id;
    char Name[200];
    int Metadata;
    
    user_devices(int usr_id, const char* name, int metadata) : user_id{usr_id},Metadata{metadata}{
        strcpy(Name,name);
    }
};
struct sensor_metadata{
    int id;
    float min_val, max_val;
    char Name[200];
    sensor_metadata(int _id, float _min_val, float _max_val, const char* _name) : id{_id}, min_val{_min_val}, max_val{_max_val} {
        strcpy(Name, _name);
    }

};

namespace db{
    inline std::unique_ptr<mysqlx::Session> session;
    inline std::unique_ptr<mysqlx::Schema> schema;
    
    void insert_new_user(std::unique_ptr<user> user_data);
    void insert_sensor_data(std::unique_ptr<sensor_value> sensor_data);
    void add_device(std::unique_ptr<user_devices> new_device);
    void init();
    void get_user_devices(std::unique_ptr<user> user,std::vector<user_devices>& devices);
    void get_sensor_data(int device_id,std::vector<sensor_value>& vals);
    void add_sensor_metadata(std::unique_ptr<sensor_metadata> metadata);
};
