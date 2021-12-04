//
//  main.cpp
//  driver
//
//  Created by Phil Huffman on 12/3/21.
//

#include <iostream>
#include "readin.hpp"
#include "arrayout.hpp"
#include "writeout.hpp"
#include "verifyarray.hpp"
#include "insertion.hpp"


int main(int argc, const char * argv[]) {
    long n;
    std::string filename("");
    
    std::cout << "Enter file name: ";
    std::cin >> filename;
    std::cout << std::endl;
    const std::string fn("/Users/prh/Keepers/code/cpp/sorts/" + filename);
    
    std::cout << "Enter sample size: ";
    std::cin >> n;
    std::cout << std::endl;
    
    const long sampleSize(n);
    
    randomWrite(fn, sampleSize);
    
    long *sample = randomRead(fn, sampleSize);
    long *samplePtrMax(sample + sampleSize);
    insertionSort(sample, samplePtrMax);
    int lines(verify(sample, samplePtrMax) ? 0 : 7);
    printArray(sample, samplePtrMax, lines);

    if (lines) {
        return 1;
    }
    
    return 0;
}
