#include "memArena.h"
#include <iostream> 
#include <ostream>
struct entity{
  int a,b;
};
int main(){
  memArena::init(1000);
  entity* new_entity = memArena::get_memory<entity>();
  new_entity->a = 10;
  new_entity->b = 12;
  std::cout << "first element " << new_entity->a << " sencond element" << new_entity->b << std::endl;
  memArena::free_memory(new_entity);
}
