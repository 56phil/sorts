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
    
    long *wPtr0Max(wPtrL + lSiz);
    long *wPtr1Max(wPtrR + rSiz);
    while (wPtrL < wPtr0Max && wPtrR < wPtr1Max) {
        if (*wPtrL <= *wPtrR) {
            *lPtr++ = *wPtrL++;
        } else {
            *lPtr++ = *wPtrR++;
        }
    }
    while (wPtrL < wPtr0Max) {
        *lPtr++ = *wPtrL++;
    }
    while (wPtrR < wPtr1Max) {
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
