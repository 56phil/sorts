//
//  arrayout.cpp
//  arrayout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "arrayout.hpp"

void printArray(int *arrPtr, int *arrPtrMax) {
    int i(60);
    while (arrPtr++ < arrPtrMax && i--)
        std::cout << std::right << std::setw(24) << *arrPtr;
    std::cout << std::endl;
}
