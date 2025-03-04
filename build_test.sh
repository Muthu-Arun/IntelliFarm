# !/bin/bash
clang++ ./tests/dbms.test.cpp ./src/dbms.cpp -I./src/ -I./vendor/mysqlx/ -L./lib/  -lmysqlcppconnx -o dbms_test

clang++ ./tests/memArena.test.cpp ./src/memArena.cpp -I./src/ -o memory_pool_test
