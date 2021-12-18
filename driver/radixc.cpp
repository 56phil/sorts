//
//  radixc.cpp
//  radixc
//
//  Created by Phil Huffman on 12/15/21.
//

#include "radixc.hpp"

void radixS(long *arr1, const long n) {
    const int shiftSize(8);
    const int ctrsSize(256);
    const int nBytes(static_cast<int>(n) * sizeof(long));
    const int shiftAmountMax(sizeof(long) * sizeof(long));
    const int mask(0xff);
    int shiftAmount(0);
    int ctrs[ctrsSize];
    long *oPtr(arr1);
    long *arr2(new long[n]);
    long *kt(arr2);
    while (shiftAmount < shiftAmountMax) {
        for (auto i(0); i < ctrsSize; i++)
            ctrs[i] = 0;
        for (auto i(0); i < n; i++)
            ctrs[(arr1[i] >> shiftAmount) & mask]++;
        for (auto i(1); i < ctrsSize; i++)
            ctrs[i] += ctrs[i - 1];
        for (auto i(n - 1); i >= 0; i--) {
            auto ndx((arr1[i] >> shiftAmount) & mask);
            arr2[--ctrs[ndx]] = arr1[i];
        }
        std::swap(arr1, arr2);
        shiftAmount += shiftSize;
    }
    
    if (arr2 == oPtr)
        memcpy(arr1, arr2, nBytes);
    
    if (arr1[n - 1] < 0)
        doNegs(oPtr, kt, n, nBytes);
    
    delete [] kt;
}

void doNegs(long *arr, long *wrk, const long n, const long nBytes) {
    memcpy(wrk, arr, nBytes);
    const long *arrEnd(arr + n);
    const long *wrkEnd(wrk + n);
    long *wPtr(wrk);
    while (*wPtr >= 0)
        wPtr++;
    while (wPtr < wrkEnd)
        *arr++ = *wPtr++;
    while (arr < arrEnd)
        *arr++ = *wrk++;
}

void radixC(std::vector<long> &v) {
    long *a(new long [v.size()]);
    long *b(a);
    for (auto w : v) {
        *b++ = w;
    }
    
    radixS(a, v.size());
    
    for (auto i(0); i < v.size(); i++)
        v[i] = a[i];
    delete [] a;
}
