//
//  main.cpp
//  driver
//
//  Created by Phil Huffman on 12/3/21.
//

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include "arrayout.hpp"
#include "readin.hpp"
#include "verifyarray.hpp"

#include "bubble.hpp"
#include "insertion.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "selection.hpp"
#include "shell.hpp"

using namespace std::chrono;

struct sortStruct {
    std::string name;
    std::function<void(long*, long*)> fn;
    long time;
};

int main(int argc, const char * argv[]) {
    std::vector<sortStruct> fns;
    
    sortStruct bubbleSort;
    bubbleSort.name = "Bubble";
    bubbleSort.fn = bubble;
    fns.emplace_back(bubbleSort);
    
    sortStruct heapSort;
    heapSort.name = "Heap";
    heapSort.fn = insertion;
    fns.emplace_back(heapSort);
    
    sortStruct insertionSort;
    insertionSort.name = "Insertion";
    insertionSort.fn = insertion;
    fns.emplace_back(insertionSort);
    
    sortStruct mergeSort    ;
    mergeSort.name = "Merge";
    mergeSort.fn = mSort;
    fns.emplace_back(mergeSort);
    
    sortStruct quickSort;
    quickSort.name = "Quick";
    quickSort.fn = quick;
    fns.emplace_back(quickSort);
    
    sortStruct selectionSort;
    selectionSort.name = "Selection";
    selectionSort.fn = selection;
    fns.emplace_back(selectionSort);
    
    sortStruct shellSort;
    shellSort.name = "Shell";
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
    long *oPtr = randomRead(fn, sampleSize);
    long *oPtrMax(oPtr + sampleSize);
    long *wPtr(new long[sampleSize]);
    long *wPtrMax(wPtr + sampleSize);
    
    for (auto f : fns) {
        memcpy(wPtr, oPtr, sampleSize);
        auto start = high_resolution_clock::now();
        f.fn(wPtr, wPtrMax);
        auto stop = high_resolution_clock::now();
        if (!verify(wPtr, wPtrMax)) {
            printArray(wPtr, wPtrMax);
            printArray(oPtr, oPtrMax);
            std::cout << "\n\t" << f.name << " algorithm needs work.\n\n";
            completionCode++;
        }
        auto duration = duration_cast<microseconds>(stop - start);
        f.time = duration.count();
        std::cout << std::right << std::setw(11) << f.time  << " µseconds used by "
        << f.name << " algorithm." << std::endl;
    }
    delete [] oPtr;
    delete [] wPtr;
        
    return completionCode;
}
