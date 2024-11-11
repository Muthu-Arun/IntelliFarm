#include "./../vendor/sqlite3/sqlite3.h"
#include <iostream>

namespace db{
struct userData{

    unsigned long id;
    std::string name;
    

};
extern sqlite3* db;
extern char* errmsg;
extern int err;
void insert(const userData&);
void initialize();
}
