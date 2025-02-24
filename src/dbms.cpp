#include "dbms.h"
#include "devapi/result.h"
#include "devapi/row.h"
#include "xdevapi.h"
#include <ctime>
#include <memory>
#include <vector>



void db::init() {
        try {
            session = std::make_unique<mysqlx::Session>("localhost", 33060, "root", "new_password");
            std::cout << "Database session initialized successfully.\n";
            schema = std::make_unique<mysqlx::Schema>(session->getSchema("intelliFarm"));
        } catch (const mysqlx::Error &err) {
            std::cerr << "Database Error: " << err.what() << std::endl;
            exit(1);
        }
}
void db::insert_new_user(std::unique_ptr<user> user_data){
    mysqlx::Table table = schema->getTable("user");
    table.insert("user_name","password","Name").values(user_data->user_name, user_data->password, user_data->name).execute();

}
void db::insert_sensor_data(std::unique_ptr<sensor_value> sensor_data){
    mysqlx::Table table = schema->getTable("sensor");
    table.insert("val","user_sensor_id").values(sensor_data->val,sensor_data->device_id).execute();
    
}
void db::add_device(std::unique_ptr<user_devices> new_device){
    mysqlx::Table table = schema->getTable("user_sensors");
    table.insert("user_id", "name", "metadata").values(new_device->user_id,new_device->Name, new_device->Metadata).execute();

}
void db::get_user_devices(std::unique_ptr<user> user,std::vector<user_devices>& devices){ 
    mysqlx::Table device_table = schema->getTable("user_sensors");
    mysqlx::Table user_table = schema->getTable("user");
    mysqlx::RowResult res = device_table.select("name","id","metadata").where("user_id = :usr_id").bind("usr_id", user->id).execute();
    for(mysqlx::Row row : res.fetchAll()){
        devices.emplace_back(user_devices(user->id,row[0].get<std::string>().c_str(),
            row[2].get<std::string>().c_str()));
    }
}
void db::get_sensor_data(int device_id,std::vector<sensor_value>& vals){
    mysqlx::Table sensor_table = schema->getTable("sensor");
    mysqlx::RowResult res = sensor_table.select("val","timestamp").where("user_sensor_id = :device_id").bind("device_id",device_id).execute();
    for(mysqlx::Row row : res.fetchAll()){
        vals.emplace_back(sensor_value(row[0].get<float>(), row[1].get<std::time_t>()));
    }
}
