//
// Created by 19143 on 2021/4/12.
//

#include "SM4.h"

//mk are encrypt keys, rk are round keys
// MK = (MK0, MK1, MK2, MK3), MKi is 32-bit
void SM4::keyexpand(uint32_t *MK, uint32_t *rk) {
    //temp K
    uint32_t K[36];

    for (int i = 0; i < 4; i++)
        K[i] = MK[i] ^ sm4_Fk[i];

    for (int i = 0; i < 32; i++)
        rk[i] = K[i + 4] = K[i] ^ permutation_T2(K[i + 1] ^ K[i + 2] ^ K[i + 3] ^ sm4_CK[i]);
}

// (b0, b1, b2, b3) = tau(a) = (sbox(a0), sbox(a1), sbox(a2), sbox(a3))
uint32_t SM4::non_lin_tran_tau(uint32_t x) {
    uint32_t ans = 0;
    for(int i = 0; i <= 24; i += 8)
        ans |= (sm4_Sbox[(x >> i) & 0xff] << i);

    return ans;
}
// L(B) = B ^ (B <<< 2) ^ (B <<< 10) ^ (B <<< 18) ^ (B <<< 24)
uint32_t SM4::linear_trans_L(uint32_t B) {
    return (B ^ ROTL32(B, 2) ^ ROTL32(B, 10) ^ ROTL32(B, 18) ^ ROTL32(B, 24));
}

//T(.)=L(τ(.)), in plain encrypt and chiper decrypt
uint32_t SM4::permutation_T(uint32_t B) {
    return linear_trans_L(non_lin_tran_tau(B));
}

// L'(B) = B ^ (B <<< 13) ^ (B <<< 23)
uint32_t SM4::linear_trans_L2(uint32_t B) {
    return (B ^ ROTL32(B, 13) ^ ROTL32(B, 23));
}
//in keyexpansion
uint32_t SM4::permutation_T2(uint32_t B) {
    return linear_trans_L2(non_lin_tran_tau(B));
}
