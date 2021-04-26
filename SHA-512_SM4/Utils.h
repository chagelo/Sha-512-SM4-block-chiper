//
// Created by 19143 on 2021/4/12.
//

#ifndef SHA_512_SM4_UTILS_H
#define SHA_512_SM4_UTILS_H

#include "global_var.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <numeric>
#include <random>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;

class Utils {
public:
    static void stringtobyte(std::string plain, uint8_t plainbyte[], const int len);
    static void substr(std::string str, uint64_t substr[], const int pos, const int len);
    static void initializehashbuffer();
    static std::vector<uint8_t> GenerateData(std::size_t bytes);
    static int _stoi(std::string mode);
    static std::vector<uint8_t> readfile(std::string path, size_t &len);
    static void writefile(std::string savefile, std::vector<uint8_t>data, size_t len, std::string suffix = "");
};


#endif //SHA_512_SM4_UTILS_H
