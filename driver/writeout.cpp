//
//  writeout.cpp
//  writeout
//
//  Created by Phil Huffman on 12/3/21.
//

#include "writeout.hpp"

void randomWrite(const std::string fn, const long nExperiments ) {
    
    std::default_random_engine generator;
    std::uniform_int_distribution<long> distribution(std::numeric_limits<long>::min(),
                                                     std::numeric_limits<long>::max());
    std::ofstream ofs;
     
    ofs.open (fn, std::ofstream::out);
    
    for (long i(nExperiments); i; --i) {
        long n(distribution(generator));
        ofs << n << '\n';
    }
    
    ofs << std::endl;
    
    ofs.close();
}
