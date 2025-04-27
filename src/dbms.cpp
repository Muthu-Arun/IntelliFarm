#include "dbms.h"
#include "xdevapi.h"
#include <cstring>



namespace db{

    void init() {
        try {
            session = std::make_unique<mysqlx::Session>("localhost", 33060, "root", "new_password");
            std::cout << "Database session initialized successfully.\n";
            schema = std::make_unique<mysqlx::Schema>(session->getSchema("intelliFarm"));
        } catch (const mysqlx::Error &err) {
            std::cerr << "Database Error: " << err.what() << std::endl;
            exit(1);
        }
        
}

void insert_new_user(const user& user_data){
    static mysqlx::Table table = schema->getTable("user");
    table.insert("user_name","password","Name").values(user_data.user_name, user_data.password, user_data.name).execute();

}
void insert_sensor_data(const sensor_value& sensor_data){
    static mysqlx::Table table = schema->getTable("sensor");
    table.insert("val","user_sensor_id").values(sensor_data.val,sensor_data.device_id).execute();
    
}
void add_device(const user_devices& new_device){
    static mysqlx::Table table = schema->getTable("user_sensors");
    table.insert("user_id", "name", "metadata").values(new_device.user_id,new_device.Name, new_device.Metadata).execute();

}
void get_user_devices(const user& user,std::vector<user_devices>& devices){ 
    static mysqlx::Table device_table = schema->getTable("user_sensors");
    static mysqlx::Table user_table = schema->getTable("user");
    mysqlx::RowResult res = device_table.select("name","id","metadata").where("user_id = :usr_id").bind("usr_id", user.id).execute();
    for(mysqlx::Row row : res.fetchAll()){
        devices.emplace_back(user_devices(user.id,row[0].get<std::string>().c_str(),
            row[2].get<int>()));
    }
}
void get_sensor_data(int device_id,std::vector<sensor_value>& vals){
    static mysqlx::Table sensor_table = schema->getTable("sensor");
    mysqlx::RowResult res = sensor_table.select("val","timestamp").where("user_sensor_id = :device_id").bind("device_id",device_id).execute();
    for(mysqlx::Row row : res.fetchAll()){
        vals.emplace_back(sensor_value(row[0].get<float>(), row[1].get<std::time_t>()));
    }
}
void add_sensor_metadata(const sensor_metadata& metadata){
    static mysqlx::Table sensor_metadata = schema->getTable("sensor_metadata");
    sensor_metadata.insert("id","name","min_val","max_val").values(metadata.id,metadata.Name,metadata.min_val,metadata.max_val).execute();
}
void add_actuator_metadata(const actuator& _actuator){
    static mysqlx::Table actuator_table = schema->getTable("actuator");
    actuator_table.insert("id","type","state","val").values(_actuator.id, _actuator.type, _actuator.state, _actuator.val);
}

}
bool sizeCheck(const char* target, size_t sze){
    if(std::strlen(target) < sze) return true;
    return false;
}