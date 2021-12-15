//
//  writeout.cpp
//  writeout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "writeout.hpp"

void randomFill(long n, std::vector<long> &v) {
    std::mt19937 generator (static_cast<unsigned int>(clock()));
    std::uniform_int_distribution<long> distribution(std::numeric_limits<long>::min(),
                                                     std::numeric_limits<long>::max());
//    std::uniform_int_distribution<long> distribution(-255, 255);
    
    v.clear();
    while (n--) {
        long r(distribution(generator));
        v.emplace_back(r);
    }
}
