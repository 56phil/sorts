//
//  readin.cpp
//  readin
//
//  Created by Phil Huffman on 12/3/21.
//

#include "readin.hpp"

long *randomRead(const std::string fn, const long nExperiments ) {
    
    if (access(fn.c_str(), R_OK) < 0) {
        randomWrite(fn, nExperiments);
    }
    
    std::ifstream ifs;
    ifs.open (fn, std::ifstream::in);
    
    if (ifs.is_open()) {
        long *sample(new long[nExperiments]);
        long *samplePtr (sample);
        const long *samplePtrMax(samplePtr + nExperiments);
        const int buffSize(2048);
        char buff[buffSize + 1];
        while (ifs.getline(buff, buffSize) && samplePtr < samplePtrMax)
            *samplePtr++ = atol(buff);
        ifs.close();
        if (samplePtr == samplePtrMax) {
            return sample;
        } else {
            randomWrite(fn, nExperiments);
            return randomRead(fn, nExperiments);
        }
    }
    
    return nullptr;
}
