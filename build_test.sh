# !/bin/bash
clang++ ./tests/dbms.test.cpp ./src/dbms.cpp -I./src/ -I./vendor/mysqlx/ -L./lib/  -lmysqlcppconnx 
