//
//  merge.cpp
//  merge
//
//  Created by Phil Huffman on 12/6/21.
//

#include "merge.hpp"

void merge(long * lPtr, long *mPtr, long *rPtr) {
    long lSiz(mPtr - lPtr + 1);
    long rSiz(rPtr - mPtr);
    
    long *wPtr0(new long [lSiz]);
    long *wPtr1(new long [rSiz]);
    
    memcpy(wPtr0, lPtr, lSiz);
    memcpy(wPtr1, mPtr, rSiz);
    
    long *wPtr0Max(wPtr0 + lSiz);
    long *wPtr1Max(wPtr1 + rSiz);
    while (lPtr < rPtr && wPtr0 < wPtr0Max && wPtr1 < wPtr1Max) {
        if (*wPtr0 < *wPtr1) {
            *lPtr++ = *wPtr0++;
        } else {
            *lPtr++ = *wPtr1++;
        }
    }
    while (wPtr0 < wPtr0Max) {
        *lPtr++ = *wPtr0++;
    }
    while (wPtr1 < wPtr1Max) {
        *lPtr++ = *wPtr1++;
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
