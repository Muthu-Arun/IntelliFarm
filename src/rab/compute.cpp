#include "compute.h"
inline bool match_size(const std::vector<size_t>& v1, const std::vector<size_t>& v2){
    if(v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size();i++) 
        if(v1[i] != v2[i]) return false;
    return true;
}
