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
#include "formattime.hpp"
#include "verifyarray.hpp"

#include "bubble.hpp"
#include "heap.hpp"
#include "insertion.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "selection.hpp"
#include "shell.hpp"
#include "stl.hpp"

using namespace std::chrono;

struct sortMetrics {
    bool error;
    long time;
    long sampleSize;
};

struct sortStruct {
    std::string name;
    std::function<void(std::vector<long> &)> fn;
    std::vector<sortMetrics> runData;
};

static void errorFunction(int &, std::vector<long>, std::vector<long>);
static void copyVector(std::vector<long> &, std::vector<long> &);

int main(int argc, const char * argv[]) {
    std::vector<sortStruct> fns;
    fns.clear();
    
    sortStruct bubbleSort;
    bubbleSort.name = "Bubble";
    bubbleSort.fn = bSort;
    bubbleSort.runData.clear();
    fns.emplace_back(bubbleSort);

    sortStruct heapSort;
    heapSort.name = "Heap";
    heapSort.fn = heap;
    heapSort.runData.clear();
    fns.emplace_back(heapSort);
    
    sortStruct insertionSort;
    insertionSort.name = "Insertion";
    insertionSort.fn = insertion;
    insertionSort.runData.clear();
    fns.emplace_back(insertionSort);
    
    sortStruct mergeSort;
    mergeSort.name = "Merge";
    mergeSort.fn = mSort;
    mergeSort.runData.clear();
    fns.emplace_back(mergeSort);
    
    sortStruct quickSort;
    quickSort.name = "Quick";
    quickSort.fn = qSort;
    quickSort.runData.clear();
    fns.emplace_back(quickSort);
    
    sortStruct selectionSort;
    selectionSort.name = "Selection";
    selectionSort.fn = selection;
    selectionSort.runData.clear();
    fns.emplace_back(selectionSort);
    
    sortStruct shellSort;
    shellSort.name = "Shell";
    shellSort.fn = shell;
    shellSort.runData.clear();
    fns.emplace_back(shellSort);
    
    sortStruct stlSort;
    stlSort.name = "STL";
    stlSort.fn = stl;
    stlSort.runData.clear();
    fns.emplace_back(stlSort);
    
    int completionCode(0);
    long sampleSizeMax(2 << 13);
    
    std::vector<long> orginalCopy;
    std::vector<long> workCopy;
    std::vector<long> checkCopy;
    
    for (long sampleSize(31); sampleSize < sampleSizeMax; (sampleSize <<= 1) |= 1) {
        std::cout << formatTime(true, true) << " n: " << sampleSize
        << " ----------\n";
        randomFill(sampleSize, orginalCopy);
        copyVector(checkCopy, orginalCopy);
        std::sort(checkCopy.begin(), checkCopy.end());
        for (auto &f : fns) {
            copyVector(workCopy, orginalCopy);
            std::cout << formatTime(false, true) << ' ' << f.name << ":\n";
            auto start = high_resolution_clock::now();
            f.fn(workCopy);
            auto stop = high_resolution_clock::now();
            long duration = duration_cast<microseconds>(stop - start).count();
            sortMetrics tm;
            tm.error = verify(workCopy, checkCopy);
            tm.time = duration;
            tm.sampleSize = sampleSize;
            if (!tm.error)
                errorFunction(completionCode, workCopy, orginalCopy);
            f.runData.emplace_back(tm);
            std::cout << formatTime(false, true) << std::right << std::setw(11)
            << tm.time << " µs used by " << f.name << ".\n\n";
        } // function loop
    } // sample size loop
    
    for (auto f : fns) {
        std::cout << '\n' << f.name << " -\n";
        for (auto d : f.runData)
            std::cout << std::right << std::setw(12) << d.sampleSize
            << std::right << std::setw(14) << d.time << (d.error ? ' ' : '*') << '\n';
        std::cout << '\n';
    }
    std::cout << std::endl;
    
    return completionCode;
}

static void errorFunction(int &completionCode, std::vector<long>wc,
                          std::vector<long>oc) {
    completionCode++;
    int n(0), w(22);
    
    auto itw(wc.begin());
    auto ito(oc.begin());
    
    std::cout << std::right << std::setw(4) << "n"
    << std::right << std::setw(w) << "original"
    << std::right << std::setw(w) << "result" << '\n';
    while (itw != wc.end() && ito != oc.end() && n < 33) {
        std::cout << std::right << std::setw(4) << ++n
        << std::right << std::setw(w) << *ito++
        << std::right << std::setw(w) << *itw++ << '\n';
        
    }
}

void copyVector(std::vector<long> &dest, std::vector<long> &source) {
    dest.clear();
    while (dest.size() < source.size())
        dest.push_back(source[dest.size()]);
}
