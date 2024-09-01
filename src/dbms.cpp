#include<iostream>
#include"sqlite3.h"

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
        std::cout<<errmsg<<"\n";
    }
    query = "SELECT * from test";
    sqlite3_exec(db,query.c_str(),callback,0,&errmsg);
    std::cout<<errmsg<<"\n";

}