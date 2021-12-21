//
//  writeout.cpp
//  writeout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "writeout.hpp"

void randomFill(long n, lv &v) {
    std::mt19937 generator (static_cast<int>(clock()));
    std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min(),
                                                     std::numeric_limits<int>::max());
//    std::uniform_int_distribution<long> distribution(-255, 255);
    
    v.clear();
    while (n--) {
        int r(distribution(generator));
        v.push_back(r);
    }
}
