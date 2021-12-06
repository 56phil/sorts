//
//  verifyarray.cpp
//  verifyarray
//
//  Created by Phil Huffman on 12/3/21.
//

#include "verifyarray.hpp"

bool verify(long *lPtr, long *rPtr) {
    long *begin(lPtr);
    while (++begin < rPtr) {
        if (*(begin - 1) > *begin) {
            std::cout << *(begin - 1) << ", " << *begin << std::endl;
            return false;
        }
    }
    return true;
}
