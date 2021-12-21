//
//  radixc.cpp
//  radixc
//
//  Created by Phil Huffman on 12/15/21.
//

#include "radixc.hpp"

void doNegs(int *arr, int *wrk, const long n, const unsigned long nBytes) {
    memcpy(wrk, arr, nBytes);
    const int *arrEnd(arr + n);
    const int *wrkEnd(wrk + n);
    int *wPtr(wrk);
    while (*wPtr >= 0)
        wPtr++;
    while (wPtr < wrkEnd)
        *arr++ = *wPtr++;
    while (arr < arrEnd)
        *arr++ = *wrk++;
}

void radixS(int *arr1, const long n) {
    const int shiftSize(8);
    const int ctrsSize(256);
    const unsigned long nBytes(n * sizeof(int));
    const int shiftAmountMax(32);
    const int mask(0xff);
    int shiftAmount(0);
    int ctrs[ctrsSize];
    int *oPtr(arr1);
    int *arr2(new int[n]);
    int *kt(arr2);
    while (shiftAmount < shiftAmountMax) {
        for (auto i(0); i < ctrsSize; i++)
            ctrs[i] = 0;
        for (auto i(0); i < n; i++)
            ctrs[getIndex(arr1[i], shiftAmount, mask)]++;
        for (auto i(1); i < ctrsSize; i++)
            ctrs[i] += ctrs[i - 1];
        for (auto i(n - 1); i >= 0; i--)
            arr2[--ctrs[getIndex(arr1[i], shiftAmount, mask)]] = arr1[i];
        std::swap(arr1, arr2);
        shiftAmount += shiftSize;
    }
    
    if (arr2 == oPtr)
        memcpy(arr1, arr2, nBytes);
    
    if (arr1[n - 1] < 0)
        doNegs(oPtr, kt, n, nBytes);
    
    delete [] kt;
}

void radixC(lv &v) {
    auto *a(new int [v.size()]);
    auto *b(a);
    for (auto w : v) {
        *b++ = w;
    }
    
    radixS(a, v.size());
    
    for (auto i(0); i < v.size(); i++)
        v[i] = a[i];
    delete [] a;
}

long getIndex(const int n, const int sa, const int mask) {
    return ((n >> sa) & mask);
}
