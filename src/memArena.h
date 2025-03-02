#include <cstddef>
#include<stdlib.h>
#include<unordered_map>
namespace memArena{
extern std::byte* rootptr ;
extern size_t avail_space;
extern std::unordered_map<size_t,size_t> memspace;
void init(size_t);
size_t search_free_spot(size_t block_size = 1);
template<typename t>
t* get_memory(size_t sze = 1){
    size_t offset = search_free_spot();
    return (t*)(rootptr+offset);
}
template<typename t>
bool free_memory(t* item){
    std::ptrdiff_t offset = item - rootptr;
    memspace.erase((size_t)offset);
}
}
