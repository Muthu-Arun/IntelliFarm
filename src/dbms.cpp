#include<iostream>
#include"./../vendor/sqlite3/sqlite3.h"
#include "./dbms.h"
static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        // std::cout<<"Running\n";
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
void test(){
    sqlite3* db;
    char* errmsg;
    int err;
    //sqlite3_open
    if(sqlite3_open("newdb.db",&db)){
        std::cout<<"Can't open Database";
        return;
    }
    std::cout<<"Database Opened\n";
    std::string query = "create table test1(id int, name varchar(30), phone char(10))";
    err = sqlite3_exec(db,query.c_str(),0,0,&errmsg);
    if(!err){
        std::cout<<"Table creation successful\n";
    }
    else{
        //std::cout<<errmsg<<"\n";
    }
    query = "SELECT * from test";
    sqlite3_exec(db,query.c_str(),callback,0,&errmsg);
    //std::cout<<errmsg<<"\n";

}
namespace db{
    sqlite3* db;
    char* errmsg;
    int err;
void insert(const userData &udt){
    std::cout << "Function Currently Empty Not Implemented\n"; 
}

void execute(const char *query){
    sqlite3_exec(db,query,0,0,&errmsg);
}
void get(weatherData &wdt){
    std::string select_sql = "SELECT * FROM WEATHER;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, select_sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
    } 
    else {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
//          int id = sqlite3_column_int(stmt, 0);
            //const char* name = (const char*)sqlite3_column_text(stmt, 1);
            //int age = sqlite3_column_int(stmt, 2);
            //const char* address = (const char*)sqlite3_column_text(stmt, 3);
            wdt.temp = sqlite3_column_double(stmt, 1);
            wdt.humidity = sqlite3_column_double(stmt, 2);
            wdt.pressure = sqlite3_column_double(stmt, 3);
            wdt.source_id = sqlite3_column_double(stmt, 0);

        std::cout << "Temperature = " << wdt.temp << ", Humidity  = " <<wdt.humidity<< ", Pressure = " << wdt.pressure << ", Source ID = " << wdt.source_id << std::endl;
    }
}
sqlite3_finalize(stmt);

}
void initialize(){

    //sqlite3_open
    if(sqlite3_open("./newdb.db",&db)){
        std::cout<<"Can't open Database";
        return;
    }
    std::cout<<"Database Opened\n";
}

}
namespace ram_cache{
db::weatherData *wdata;
void initialize(){
    wdata = new db::weatherData;
}
void update(const db::weatherData &data){
    wdata->temp = data.temp;
    wdata->humidity = data.humidity;
    wdata->pressure = data.pressure;
    // copies only partial data


}
void get (db::weatherData &data){
    data.temp = wdata->temp;
    data.humidity = wdata->humidity;
    data.pressure = wdata->pressure;

}
    }
