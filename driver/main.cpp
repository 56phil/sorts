//
//  main.cpp
//  driver
//
//  Created by Phil Huffman on 12/3/21.
//

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>
#include "arrayout.hpp"
#include "formattime.hpp"
#include "verifyarray.hpp"

#include "bubble.hpp"
#include "heap.hpp"
#include "insertion.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "radixsort.hpp"
#include "selection.hpp"
#include "shell.hpp"
#include "stl.hpp"

using namespace std::chrono;

typedef std::vector<long> lv;

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

struct my_numpunct : std::numpunct<char> {
    std::string do_grouping() const {return "\03";}
};

static void errorFunction(int &, lv, lv);
static void copyVector(lv &, lv &);
static void makeFile(std::vector<sortStruct>);
static std::string convertMicroSeconds(long);

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
    
    sortStruct radixSort;
    radixSort.name = "Radix";
    radixSort.fn = radSort;
    radixSort.runData.clear();
    fns.emplace_back(radixSort);
    
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
    int n0(8192);
    int wdth(20);
    long sampleSizeMax(128 << 13);
    
    lv orginalCopy;
    lv workCopy;
    lv checkCopy;
    
    std::locale loc (std::cout.getloc(),new my_numpunct);
    std::cout.imbue(loc);
    
    std::cout << "Start: " << n0 << "  Max: " << sampleSizeMax << '\n';
    
    for (long sampleSize(n0); sampleSize < sampleSizeMax; (sampleSize <<= 1)) {
        std::cout << '\n' << formatTime(true, true) << " n: " << sampleSize
        << " -------------\n";
        randomFill(sampleSize, orginalCopy);
        copyVector(checkCopy, orginalCopy);
        std::sort(checkCopy.begin(), checkCopy.end());
        for (auto &f : fns) {
            copyVector(workCopy, orginalCopy);
            auto start = high_resolution_clock::now();
            f.fn(workCopy);
            auto stop = high_resolution_clock::now();
            long duration = duration_cast<microseconds>(stop - start).count();
            std::cout << formatTime(false, true) << std::right << std::setw(11)
            << f.name << ": " <<std::setw(wdth) <<std::right << duration << " µs" << "\n";
            sortMetrics tm;
            tm.error = verify(workCopy, checkCopy);
            tm.time = duration;
            tm.sampleSize = sampleSize;
            if (!tm.error)
                errorFunction(completionCode, workCopy, orginalCopy);
            f.runData.emplace_back(tm);
        } // function loop
        makeFile(fns);
    } // sample size loop
    
    for (auto f : fns) {
        std::cout << '\n' << f.name << " -\n";
        for (auto d : f.runData)
            std::cout << std::right << std::setw(12) << d.sampleSize
            << std::right << std::setw(14) << d.time << (d.error ? "  " : "* ")
            << convertMicroSeconds(d.time) << '\n';
        std::cout << '\n';
    }
    std::cout << std::endl;
    
    return completionCode;
}

static void errorFunction(int &completionCode, lv wc, lv oc) {
    completionCode++;
    int n(0), w(28);
    
    auto itw(wc.begin());
    auto ito(oc.begin());
    
    std::cout << std::right << std::setw(4) << "n"
    << std::right << std::setw(w) << "original"
    << std::right << std::setw(w) << "result" << '\n';
    while (itw != wc.end() && ito != oc.end() && n < 33)
        std::cout << std::right << std::setw(4) << ++n
        << std::right << std::setw(w) << *ito++
        << std::right << std::setw(w) << *itw++ << '\n';
}

static void copyVector(lv &dest, lv &source) {
    dest.clear();
    while (dest.size() < source.size())
        dest.push_back(source[dest.size()]);
}

static void makeFile(std::vector<sortStruct> v) {
    std::fstream fst;
    fst.open("/Users/prh/Keepers/code/cpp/sorts/list.csv", std::ios::out);
    fst << "Algorithm";
    for (auto rd : v[0].runData) {
        fst << ','<< '\"' << rd.sampleSize << '\"';
    }
    fst << '\n';
    for (auto s : v) {
        fst << s.name;
        for (auto rd : s.runData) {
            fst << ',' << rd.time;
        }
        fst << '\n';
    }
    fst.close();
}

static std::string convertMicroSeconds(long timestamp) {
    long milliseconds = (long) (timestamp / 1000000) % 1000;
    long seconds = (((long) (timestamp / 1000) - milliseconds) / 1000) % 60;
    long minutes = (((((long) (timestamp / 1000) - milliseconds) / 1000)
                        - seconds) / 60) % 60;
    long hours = ((((((long) (timestamp / 1000) - milliseconds) / 1000)
                         - seconds) / 60) - minutes) / 60;
    
    std::stringstream sst;
    sst << std::setfill('0');
    if (hours > 0)
        sst << hours << ":";
    
    if (minutes > 0)
        sst << (hours > 0 ? "" : "   ") << std::fixed
        << std::setw(minutes > 9 || hours > 0 ? 2 : 1)
        << minutes << ":";
        
    sst << (hours == 0 && minutes == 0 ? "      " : "") << std::fixed
    << std::setw(minutes > 0 || seconds > 9 ? 2 : 1)
    << seconds << "." << milliseconds;
            
    return sst.str();
    
}
