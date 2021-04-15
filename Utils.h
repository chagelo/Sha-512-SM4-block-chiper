//
// Created by 19143 on 2021/4/12.
//

#ifndef SHA_512_SM4_UTILS_H
#define SHA_512_SM4_UTILS_H

#include "global_var.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Utils {
public:
    static void stringtobyte(string plain, uint8_t plainbyte[], const int len);
    static void substr(string str, uint64_t substr[], const int pos, const int len);
    static void initializehashbuffer();
};


#endif //SHA_512_SM4_UTILS_H
