//
// Created by 19143 on 2021/4/12.
//

#include "Sha.h"

void Sha::expandpwd(string &pwd) {
    int  len = pwd.length();
    uint64_t prelen = pwd.length() * 8;

    // fill pwd so that reminder of len divided by 1024 equals to 896
    for (int i = 0; ; ++i) {
        if (i != 0 and 8 * len % 1024 == 896)
            break;
        pwd += (char)sha_padding[i];
        ++len;
    }

    // fill pwd to make its len be multiple of 1024
    uint8_t temp[16];
    for (int i = 15; i >= 0; --i) {
        temp[i] = prelen % 256;
        prelen /= 256;
    }
    for (int i = 0; i < 16; ++i)
        pwd += (char)temp[i];
}

void Sha::process(string pwd, uint64_t *H) {
    expandpwd(pwd);
    const int len = pwd.length();
    uint64_t block[16] = {0};
    Utils::initializehashbuffer();

    // 1024bits are 128bytes
    //handle each block
    for (int i = 0 ;i < len; i += 128) {
        Utils::substr(pwd, block, i, 128);
//        for (int i = 0; i < 16; i++)
//                printf("%llx ", block[i]);
//        printf("\n");
        blockhash(block, H);
    }

    // key of SM4 is 128-bit,  but we generate 512-bit information by Sha
    //TODO: fetch 128 bits from 512 bits(16 uint64_t, block[]), and send to SM4
}

// handle one block,  80 rounds
void Sha::blockhash(uint64_t *plain, uint64_t *H) {
    // generate W
    uint64_t W[80];
    expandW(plain, W);

    //80 rounds function
    // record H[i - 1]
    H[0] = hashbuffer_a, H[1] = hashbuffer_b;
    H[2] = hashbuffer_c, H[3] = hashbuffer_d;
    H[4] = hashbuffer_e, H[5] = hashbuffer_f;
    H[6] = hashbuffer_g, H[7] = hashbuffer_h;


    for (int i = 0; i < 80; ++i) {
        round(W[i], sha_Kt[i], H);
        //printf("W[i]: %llx K[i]: %llx\n", W[i], sha_Kt[i]);
    }
    nextroundH(H);

}

// initialize hash buffer, 8 64-bit registers:a,b,c,d,e,f,g,h, total 512 bits

void Sha::  expandW(uint64_t *plain, uint64_t *W) {
    for (int i = 0; i < 16; ++i)
        W[i] = plain[i];

    for (int i = 16; i < 80; ++i)
        W[i] = Sigma1(W[i - 2]) + W[i - 7] + Sigma0(W[i - 15])  +W[i - 16];
}

void Sha::round(uint64_t W, uint64_t K, uint64_t *H) {
    uint64_t T1 = H[7] + Ch(H[4], H[5], H[6]) +
            Gamma1(H[4]) + W + K;
    uint64_t T2 = Gamma0(H[0]) + Maj(H[0], H[1], H[2]);
    H[7] = H[6];
    H[6] = H[5];
    H[5] = H[4];
    H[4] = H[3] + T1;
    H[3] = H[2];
    H[2] = H[1];
    H[1] = H[0];
    H[0] = T1 + T2;
}

// generate H[i - 1][]
// TODO: use H[0-7] or hashbuffer_a...
void Sha::nextroundH(uint64_t *H) {
    H[0] = H[0] + hashbuffer_a, H[1] = H[1] + hashbuffer_b;
    H[2] = H[2] + hashbuffer_c, H[3] = H[3] + hashbuffer_d;
    H[4] = H[4] + hashbuffer_e, H[5] = H[5] + hashbuffer_f;
    H[6] = H[6] + hashbuffer_g, H[7] = H[7] + hashbuffer_h;
}

void Sha::print() {
    printf("%llx %llx %llx %llx %llx %llx %llx %llx\n", hashbuffer_a, hashbuffer_b,
             hashbuffer_c, hashbuffer_d, hashbuffer_e, hashbuffer_f, hashbuffer_g, hashbuffer_h);
}

uint64_t Sha::Gamma0(uint64_t x) {
    return (ROTR64(x, 28) ^ ROTR64(x, 34) ^ ROTR64(x,39));
}

uint64_t Sha::Gamma1(uint64_t x) {
    return (ROTR64(x, 14) ^ ROTR64(x, 18) ^ ROTR64(x,41));
}

uint64_t Sha::Sigma0(uint64_t x) {
    return (ROTR64(x, 1) ^ ROTR64(x, 8) ^ SHR(x, 7));
}

uint64_t Sha::Sigma1(uint64_t x) {
    return (ROTR64(x, 19) ^ ROTR64(x, 61) ^ SHR(x, 6));
}
