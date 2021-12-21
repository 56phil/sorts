//
//  main.cpp
//  driver
//
//  Created by Phil Huffman on 12/3/21.
//

#include "driver.hpp"

struct sortMetrics {
    bool error;
    long time;
    long sampleSize;
};

struct sortStruct {
    std::string name;
    std::function<void(lv &)> fn;
    std::vector<sortMetrics> runData;
};

struct my_numpunct : std::numpunct<char> {
    std::string do_grouping() const {return "\03";}
};

static void errorFunction(int &, lv, lv);
static void copyVector(lv &, lv &);
static void makeFile(std::vector<sortStruct>);
static std::string convertMicroSeconds(long);
static void testConvert();

int main(int argc, const char * argv[]) {
    std::locale loc (std::cout.getloc(),new my_numpunct);
    std::cout.imbue(loc);
    
    testConvert();
    
    std::vector<sortStruct> fns;
    fns.clear();
    
    sortStruct bubbleSort;
    bubbleSort.name = "Bubble";
    bubbleSort.fn = bSort;
    bubbleSort.runData.clear();
    fns.emplace_back(bubbleSort);
    
    sortStruct stlSort;
    stlSort.name = "CPP Default";
    stlSort.fn = stl;
    stlSort.runData.clear();
    fns.emplace_back(stlSort);

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
    
    sortStruct radixSortC;
    radixSortC.name = "Radix";
    radixSortC.fn = radixC;
    radixSortC.runData.clear();
    fns.emplace_back(radixSortC);
    
    sortStruct radixSort;
    radixSort.name = "Radix w/STL";
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
    
    int completionCode(0);
    int wdth(22);
    long ssMin(1 << 8);
    long ssMax(1 << 17);
//    ssMax <<= 2;
    
    lv orginalCopy;
    lv workCopy;
    lv checkCopy;
    
    std::cout << "\nStart: " << ssMin << "  Max: " << ssMax << '\n';
    
    for (long sampleSize(ssMin); sampleSize < ssMax; (sampleSize <<= 1)) {
        std::cout << '\n' << formatTime(true, true) << " n: " << std::right
        << std::setw(14) << sampleSize << " ----------\n";
        randomFill(sampleSize, orginalCopy);
        copyVector(checkCopy, orginalCopy);
        std::sort(checkCopy.begin(), checkCopy.end());
        for (auto &f : fns) {
            copyVector(workCopy, orginalCopy);
            auto start = high_resolution_clock::now();
            f.fn(workCopy);
            auto stop = high_resolution_clock::now();
            long duration = duration_cast<microseconds>(stop - start).count();
            std::cout << formatTime(false, true) << std::right << std::setw(13)
            << f.name << ": " <<std::setw(wdth) <<std::right << duration << " µs"
            << convertMicroSeconds(duration) << "\n";
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
    dest = source;
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

static std::string convertMicroSeconds(long tms) {
    const long ku(1000000);
    long fractional(tms % ku);
    long seconds(tms / ku);
    long minutes(seconds / 60);
    seconds -= minutes * 60;
    long hours(minutes / 60);
    minutes -= hours * 60;

    std::stringstream sst;
    sst << std::setfill(' ');
    if (hours > 0)
        sst << (hours > 99 ? "  " : hours > 9 ? "   " : "    " ) << hours << ":";
    else
        sst << "    ";
    
    sst << std::setfill('0');
    if (minutes > 0 || hours > 0)
        sst << (hours > 0 ? "" : minutes > 9 ? "  " : "   ") << std::fixed
        << std::setw(minutes > 9 || hours > 0 ? 2 : 1)
        << minutes << ":";
    
    sst << (hours == 0 && minutes == 0 && seconds < 10 ? "      " : hours == 0 && minutes == 0 ? "     " : "")
    << std::fixed
    << std::setw(hours == 0 && minutes == 0 && seconds < 10 ? 1 : 2)
    << seconds << "." << std::setw(6) << fractional;
    
    return sst.str();
}

static void testConvert() {
    for (long i(1); i < 1000000000000; i *= 13 ) {
       std::cout << std::right << std::setw(16) << i << '\t' << convertMicroSeconds(i) << '\n';
    }
}
