#include "memArena.h"
#include <exception>
#include <unordered_map>

namespace memArena{
std::byte* rootptr = nullptr;
size_t avail_space = 0;
std::unordered_map<size_t,size_t> memspace;
void init(size_t sze){
    rootptr =static_cast<std::byte*>(malloc(sze*((size_t) 1)));
    avail_space = sze;

}
size_t search_free_spot(size_t block_size){
    size_t i = 0;
    while(i<avail_space){
        auto iter = memspace.find(i);
        if(iter == memspace.end()){
            memspace[i] = block_size;
            return i;
        }
    i+= memspace[i];

    }
    throw new std::exception;
}

}
