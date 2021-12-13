//
//  verifyarray.cpp
//  verifyarray
//
//  Created by Phil Huffman on 12/3/21.
//

#include "verifyarray.hpp"

bool verify(std::vector<long>wc, std::vector<long>oc) {
    auto itw(wc.begin());
    auto ito(oc.begin());
    while (itw != wc.end() && ito != oc.end()) {
        if (*itw++ != *ito++) {
            return false;
        }
    }
    return true;
}
