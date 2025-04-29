#pragma once
#include <cassert>
#include <cstddef>
#include<iostream>
#include<vector>
#include<thread>
#include<cmath>

inline bool match_size(const std::vector<size_t>& , const std::vector<size_t>& );

namespace compute {
    template<typename t>
    void add_tensor(t* t1, t* t2,const std::vector<size_t>& dims){
        for (size_t sze : dims) {
            
        }
    }
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
