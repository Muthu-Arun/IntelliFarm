#include<dbms.h>
#include <memory>
#include <iostream>

void test_user_insert(){
  std::unique_ptr<user> user_test = std::make_unique<user>("user_1","new_password","Arun");
  db::insert_new_user(std::move(user_test));
}

void test_sensor_value_insert(int device_id = 1, float val = 34.6){
  std::unique_ptr<sensor_value> sensor_test = std::make_unique<sensor_value>(val,device_id);
  db::insert_sensor_data(std::move(sensor_test));
}

int main(){
  std::cout << "Size of User "<< sizeof(user) << "\n";
  db::init();
  test_user_insert();
  //test_sensor_value_insert();

}
