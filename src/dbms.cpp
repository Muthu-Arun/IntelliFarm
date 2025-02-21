#include "dbms.h"
#include "xdevapi.h"
#include <memory>



void db::init() {
        try {
            session = std::make_unique<mysqlx::Session>("localhost", 33060, "root", "new_password");
            std::cout << "Database session initialized successfully.\n";
            schema = std::make_unique<mysqlx::Schema>(session->getSchema("intelliFarm");
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
