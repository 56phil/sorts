//
//  arrayout.cpp
//  arrayout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "arrayout.hpp"

void printArray(long *arrPtr, long *arrPtrMax) {
    int i(60);
    for (long *ptr(arrPtr); ptr < arrPtrMax && i; ptr++, --i) {
        std::cout << std::right << std::setw(24) << *ptr;
    }
    std::cout << std::endl;
}
