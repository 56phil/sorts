//
//  verifyarray.cpp
//  verifyarray
//
//  Created by Phil Huffman on 12/3/21.
//

#include "verifyarray.hpp"

bool verify(long *lPtr, long *rPtr) {
    long *wPtr(lPtr);
    while (++wPtr < rPtr) {
        if (*(wPtr - 1) > *wPtr) {
            return false;
        }
    }
    return true;
}
