//
// Created by 19143 on 2021/4/14.
//

#ifndef SHA_512_SM4_CONST_H
#define SHA_512_SM4_CONST_H

#include <cstdint>
#include <iostream>
#include <cstring>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::swap;

//if x, then y, otherwise z
#define Ch(x, y, z) ((x & y) ^ ((~x) & z))
// it's true if and only if most variables are true
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
//cyclically rotates uint64_t x over n bits to the right
#define ROTR64(x, n) ((x >> n) | (x << (64 - n)))
//cyclically rotates uint32_t x over n bits to the left
#define ROTL32(x, n) ((x << n) | (x >> (32 - n)))
// shift x n bits by right
#define SHR(x, n) (x >> n)


// five modes
#define ECB 0
#define CBC 1
#define CFB 2
#define OFB 3
#define CTR 4

/*
 * Gamma0/1, Siama0/1 belong to Sha, so make update that put them into Sha.cpp
 */
//#define Gamma0(x) (ROTR64(x, 28) ^ ROTR64(x, 34) ^ ROTR64(x,39))
//#define Gamma1(x) (ROTR64(x, 14) ^ ROTR64(x, 18) ^ ROTR64(x,41))
//#define Sigma0(x) (ROTR64(x, 1) ^ ROTR64(x, 8) ^ SHR(x, 7))
//#define Sigma1(x) (ROTR64(x, 19) ^ ROTR64(x, 61) ^ SHR(x, 6))


/*
 * also, L'(B) and L(B) belong to SM4, so make update that put them into sm4.cpp
 */
// L'(B) = B ^ (B <<< 13) ^ (B <<< 23)
//#define lineartrans_L2(B) (B ^ ROTL32(B, 13) ^ ROTL32(B, 23))
// L(B) = B ^ (B <<< 2) ^ (B <<< 10) ^ (B <<< 18) ^ (B <<< 24)
//#define lineartrans_L1(B) (B ^ ROTL32(B, 2) ^ ROTL32(B, 10) ^ ROTL32(B, 18) ^ ROTL32(B, 24))

// fill pwd so that reminder of len divided by 1024 equals to 896
extern const uint8_t sha_padding[128];
//80 SHA-512 round consts
extern const uint64_t sha_Kt[80];
//system parameter FK
extern const uint32_t sm4_Fk[4];
// constant parameter CK
extern const uint32_t sm4_CK[32];
//sm4 S-box
extern const uint8_t sm4_Sbox[256];



#endif //SHA_512_SM4_CONST_H

