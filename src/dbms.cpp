#include "dbms.h"
#include <algorithm>
void ram_cache::initialize() { wdata = new weatherData; }
namespace db {
void init() {
  try {
    sql::mysql::MySQL_Driver *driver = sql::mysql::get_driver_instance();
    std::unique_ptr<sql::Connection> conn(
        driver->connect("tcp://localhost:3306", "root", "new_password"));
    conn->setSchema("intelliFarm");

  } catch (sql::SQLException &e) {
    std::cerr << "Database Exception : " << e.what() << '\n';
  }
}
} // namespace db
