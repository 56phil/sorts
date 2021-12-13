//
//  writeout.cpp
//  writeout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "writeout.hpp"

void randomFill(long n, std::vector<long> &oc) {
    std::default_random_engine generator;
    std::uniform_int_distribution<long> distribution(std::numeric_limits<long>::min(),
                                                     std::numeric_limits<long>::max());
    
    oc.clear();
    while (oc.size() < n) {
        long r(distribution(generator));
        oc.emplace_back(r);
    }
}
