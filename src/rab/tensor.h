#include "compute.h"
#include <cassert>
template<typename t>
class tensor{
    private:
        t* data = nullptr;
        std::vector<size_t> m_dims;
        bool memory_alloc(){
            size_t s = 1;
            for(size_t i : m_dims){s*= i;}
            data = new t[s];
            
        }
    public:
        tensor() = default;
        tensor(std::vector<size_t> dims): m_dims(dims) {}
        ~tensor(){
            delete [] data;
        }
        tensor<t> operator+(const tensor<t>& other){
            assert(match_size(this->m_dims, other.m_dims));
            

        }
        tensor<t> operator-(const tensor<t>& other){
            assert(match_size(this->m_dims, other.m_dims));
        }
        // FOR MATRIX MUL NOT ELEMENT - ELEMENT
        tensor<t> operator*(const tensor<t>& other){
            assert(match_size(this->m_dims, other.m_dims));
        }
        tensor<t> operator/(const tensor<t>& other){
            assert(match_size(this->m_dims, other.m_dims));
        }





};