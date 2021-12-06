//
//  arrayout.cpp
//  arrayout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "arrayout.hpp"

void printArray(long *arrPtr, long *arrPtrMax, long n) {
    int i(0);
    for (long *ptr(arrPtr); ptr < arrPtrMax && n > ++i; ptr++) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;
}
