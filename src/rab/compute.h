#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<cmath>

namespace compute {
template <typename t>
t sum(const std::vector<t>& data){
    t sum = 0;
    for(t item : data){
        sum += item;
    }
    return sum;
}
template <typename t>
double mean(const std::vector<t>& data){
    return sum(data)/data.size();

}
template <typename t>
double calculate_standard_deviation(const std::vector<t>& data) {
    double mean = mean(data);
    double sum = 0.0;

    for (t value : data) {
        sum += (value - mean) * (value - mean);
    }

    return std::sqrt(sum / data.size()); 
}

}
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
        tensor(std::vector<size_t> dims): m_dims(dims){

        }
        ~tensor(){
            delete [] data;
        }




};
