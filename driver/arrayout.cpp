//
//  arrayout.cpp
//  arrayout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "arrayout.hpp"

void printArray(long *arrPtr, long *arrPtrMax) {
    for (long *ptr(arrPtr); ptr < arrPtrMax; ptr++) {
        std::cout << *ptr << " ";
    }
    std::cout << std::endl;
}
