//
// Created by 19143 on 2021/4/12.
//

#ifndef SHA_512_SM4_SHA_H
#define SHA_512_SM4_SHA_H

#include "Utils.h"
#include "const.h"

class Sha {
private:
    static void expandpwd(string &pwd);
    static void blockhash(uint64_t *plain, uint64_t *H);
    static void round(uint64_t W, uint64_t K, uint64_t *H);
    static void expandW(uint64_t *plain, uint64_t *W);
    static void nextroundH(uint64_t H[8]);

    static uint64_t Gamma0(uint64_t x);
    static uint64_t Gamma1(uint64_t x);
    static uint64_t Sigma0(uint64_t x);
    static uint64_t Sigma1(uint64_t x);
public:

    static void process(string pwd, uint64_t *H);
    static void print();
};

#endif //SHA_512_SM4_SHA_H
