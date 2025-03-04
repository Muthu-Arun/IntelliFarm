#include "memArena.h"
#include <cstddef>
#include <utility>

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
void print_memory_pool_details(){
    std::cout << "Used Spots\n";
    for(const std::pair<size_t,size_t>& pair: memspace){
        std::cout << "Starting : " << pair.first << "Block Size " << pair.second <<"\n";
    }
}

}
