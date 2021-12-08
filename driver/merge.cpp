//
//  merge.cpp
//  merge
//
//  Created by Phil Huffman on 12/6/21.
//

#include "merge.hpp"

void merge(long * lPtr, long *mPtr, long *rPtr) {
    long lSiz(mPtr - lPtr);
    long rSiz(rPtr - mPtr);
    
    long *wPtrL(new long [lSiz]);
    long *wPtrR(new long [rSiz]);
    
    memcpy(wPtrL, lPtr, lSiz);
    memcpy(wPtrR, mPtr, rSiz);
    
    long *wPtrLMax(wPtrL + lSiz);
    long *wPtrRMax(wPtrR + rSiz);
    
    while (wPtrL < wPtrLMax && wPtrR < wPtrRMax) {
        if (*wPtrL <= *wPtrR)
            *lPtr++ = *wPtrL++;
        else
            *lPtr++ = *wPtrR++;
    }
    
    while (wPtrL < wPtrLMax) {
        *lPtr++ = *wPtrL++;
    }
    
    while (wPtrR < wPtrRMax) {
        *lPtr++ = *wPtrR++;
    }
}

void mSort(long *lPtr, long *rPtr) {
    if (lPtr >= rPtr) {
        return;
    }
    
    long *mPtr(lPtr + ((rPtr - lPtr) >> 1));
    
    mSort(lPtr, mPtr);
    mSort(mPtr + 1, rPtr);
    merge(lPtr, mPtr, rPtr);
}
