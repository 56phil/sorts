//
//  verifyarray.cpp
//  verifyarray
//
//  Created by Phil Huffman on 12/3/21.
//

#include "verifyarray.hpp"

bool verify(long *begin, long *end) {
    while (++begin < end) {
        if (*(begin - 1) > *begin) {
            return false;
        }
    }
    return true;
}
