//
//  readin.cpp
//  readin
//
//  Created by Phil Huffman on 12/3/21.
//

#include "readin.hpp"

long *randomRead(const std::string fn, const long nExperiments ) {
    
    long *sample(new long[nExperiments]);
    long *samplePtr (sample);
    const long *samplePtrMax(samplePtr + nExperiments);
    std::ifstream ifs;
    
    ifs.open (fn, std::ifstream::in);
    
    if (ifs.is_open()) {
        const int buffSize(2048);
        char buff[buffSize + 1];
        while (ifs.getline(buff, buffSize) && samplePtr < samplePtrMax) {
            *samplePtr++ = atol(buff);
        }
        ifs.close();
    }
    
    return sample;
}
