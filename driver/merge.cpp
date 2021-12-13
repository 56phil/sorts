//
//  merge.cpp
//  merge
//
//  Created by Phil Huffman on 12/6/21.
//

#include "merge.hpp"

void merge(std::vector<long> &v, std::vector<long> v1, std::vector<long> v2) {
    v.clear();
    auto it1(v1.begin()), it2(v2.begin());
    while (it1 != v1.end() && it2 != v2.end())
        if (*it1 <= *it2)
            v.push_back(*it1++);
        else
            v.push_back(*it2++);
    
    while (it1 != v1.end())
        v.push_back(*it1++);
    
    while (it2 != v2.end())
        v.push_back(*it2++);
    
}

void mSort(std::vector<long> &v) {
    if (v.size() > 1) {
        std::vector<long> v1;
        std::vector<long> v2;
        auto mp(v.size() >> 1);
        for (long i(0); i < mp; i++)
            v1.push_back(v[i]);
        for (long i(0); i < v.size() - mp; i++)
            v2.push_back(v[mp + i]);
        mSort(v1);
        mSort(v2);
        merge(v, v1, v2);
    }
}
