//
//  main.cpp
//  driver
//
//  Created by Phil Huffman on 12/3/21.
//

#include <chrono>
#include <iostream>
#include <vector>
#include "arrayout.hpp"
#include "functions.hpp"
#include "readin.hpp"
#include "verifyarray.hpp"

#include "insertion.hpp"
#include "quick.hpp"
#include "shell.hpp"

using namespace std::chrono;

struct sortStruct {
    std::string name;
    std::function<void(long*, long*)> fn;
};

int main(int argc, const char * argv[]) {
    std::vector<sortStruct> fns;
    
    sortStruct insertionSort;
    insertionSort.name = "Insertion";
    insertionSort.fn = insertion;
    fns.emplace_back(insertionSort);
    
    sortStruct quickSort;
    quickSort.name = "Quick";
    quickSort.fn = quick;
    fns.emplace_back(quickSort);
    
    sortStruct shellSort;
    shellSort.name = "shell";
    shellSort.fn = shell;
    fns.emplace_back(shellSort);
    
    int completionCode(0);
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
    
    for (auto f : fns) {
        long *sample = randomRead(fn, sampleSize);
        if (sample) {
            long *samplePtrMax(sample + sampleSize);
            auto start = high_resolution_clock::now();
            f.fn(sample, samplePtrMax);
            auto stop = high_resolution_clock::now();
            if (!verify(sample, samplePtrMax)) {
                printArray(sample, samplePtrMax, sampleSize);
                std::cout << "\n\t" << f.name << "ALGORITH FAILED" << std::endl;
                completionCode |= 1;
            }
            delete [] sample;
            auto duration = duration_cast<microseconds>(stop - start);
            std::cout << f.name << " used " << duration.count() << " µseconds" << std::endl;
        }
    }
        
    return completionCode;
}

/*
 */
