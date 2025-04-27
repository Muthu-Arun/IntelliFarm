#include<dbms.h>
#include <memory>
#include <iostream>

void test_user_insert(){
  std::unique_ptr<user> user_test = std::make_unique<user>("user_1","new_password","Arun");
  db::insert_new_user(std::move(user_test));
}

void test_sensor_value_insert(int device_id = 3, float val = 34.6){
  std::unique_ptr<sensor_value> sensor_test = std::make_unique<sensor_value>(val,device_id);
  db::insert_sensor_data(std::move(sensor_test));
}
void test_device_insert(){
  std::unique_ptr<user_devices> device = std::make_unique<user_devices>(8,"device_1",1);
  db::add_device(std::move(device));
}
void test_metadata_insert(){
  std::unique_ptr<sensor_metadata> metadata = std::make_unique<sensor_metadata>(1,0,100,"sensor - 1");
  db::add_sensor_metadata(std::move(metadata));
}
int main(){
  std::cout << "Size of User "<< sizeof(user) << "\n";
  db::init();
 // test_metadata_insert(); 
 // test_device_insert();
  test_sensor_value_insert();

}
