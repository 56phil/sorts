//
//  readin.cpp
//  readin
//
//  Created by Phil Huffman on 12/3/21.
//

#include "readin.hpp"

void randomRead(const std::string fn, const long n, long *lPtr) {
    std::ifstream ifs;
    
    if (access(fn.c_str(), R_OK) < 0) {
        randomFill(n, oc);
    } else {
        ifs.open (fn, std::ifstream::in);
        if (ifs.is_open()) {
            long *sample(new long[n]);
            long *samplePtr (sample);
            const long *samplePtrMax(samplePtr + n);
            const int buffSize(2048);
            char buff[buffSize + 1];
            while (ifs.getline(buff, buffSize) && samplePtr < samplePtrMax)
                *samplePtr++ = atol(buff);
            ifs.close();
        }
    }
}
