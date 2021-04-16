//
// Created by 19143 on 2021/4/12.
//

#include "SM4.h"

// mk are encrypt keys, rk are round keys
// MK = (MK0, MK1, MK2, MK3), MKi is 32-bit
void SM4::keyexpand(uint32_t *MK, uint32_t *rk, const int cryptflag) {
    // temp K
    uint32_t K[36];

    for (int i = 0; i < 4; i++)
        K[i] = MK[i] ^ sm4_Fk[i];

    for (int i = 0; i < 32; i++)
        rk[i] = K[i + 4] = K[i] ^ permutation_T2(K[i + 1] ^ K[i + 2] ^ K[i + 3] ^ sm4_CK[i]);

    if (cryptflag == 1)
        for (int i = 0; i < 16; ++i)
            swap(rk[i], rk[31 - i]);
}

// (b0, b1, b2, b3) = tau(a) = (sbox(a0), sbox(a1), sbox(a2), sbox(a3))
uint32_t SM4::non_lin_tran_tau(uint32_t x) {
    uint32_t ans = 0;
    for(int i = 0; i <= 24; i += 8)
        ans |= (uint32_t)(sm4_Sbox[(x >> i) & 0xff] << i);

    return ans;
}
// L(B) = B ^ (B <<< 2) ^ (B <<< 10) ^ (B <<< 18) ^ (B <<< 24)
uint32_t SM4::linear_trans_L(uint32_t B) {
    return (B ^ ROTL32(B, 2) ^ ROTL32(B, 10) ^ ROTL32(B, 18) ^ ROTL32(B, 24));
}

// T(.)=L(τ(.)), in plain encrypt and chiper decrypt
uint32_t SM4::permutation_T(uint32_t B) {
    return linear_trans_L(non_lin_tran_tau(B));
}

// L'(B) = B ^ (B <<< 13) ^ (B <<< 23)
uint32_t SM4::linear_trans_L2(uint32_t B) {
    return (B ^ ROTL32(B, 13) ^ ROTL32(B, 23));
}
// in keyexpansion
uint32_t SM4::permutation_T2(uint32_t B) {
    return linear_trans_L2(non_lin_tran_tau(B));
}

// encrypt or decrypt one block
void SM4::block_crypt(uint32_t *plainblock, uint32_t *rk) {
    uint32_t x[36];
    for (int i = 0; i < 4; ++i)
        x[i] = plainblock[i];

    for (int i = 0; i < 32; ++i)
        x[i + 4] = x[i] ^ permutation_T(x[i + 1] ^ x[i + 2] ^ x[i + 3] ^ rk[i]);

    // write encrypted chiper into plain array;
    for (int i = 0; i < 4; ++i)
        plainblock[i] = x[35 - i];
}

// TODO
void SM4::preprocess(string plainpath, string pwd) {
    // get round keys
    uint32_t MK[4];
    uint64_t H[8];
    Sha::process(pwd, H);
    for (int i = 0; i < 8; ++i)
        MK[i] = H[i / 2];

}

// len represent the number of bytes of plain, rk represent round keys
void SM4::crypt_ecb(uint32_t *plain, const int len, uint32_t *rk) {
    uint32_t temp[4];
    for (int i = 0; i < len; i += 4) {
        block_crypt(plain + i, rk);
    }
}

/*
 * n = NBlocks(P, b)
 * C_1 = SM4Encrypt(P_1 xor IV, K)
 * for i = 2 to n
 *   C_i = SM4Encrypt(P_i xor C_{i - 1}, K)
 * end for
 * C = C_1 || ... || C_n
 * */

// len represent the number of bytes of plain, rk represent round keys
void SM4::encrypt_cbc(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    // first Input1 = IV ^ plain_1
    for (int i = 0; i < 4; ++i)
        plain[i] = plain[i] ^ IV[i];
    block_crypt(plain, rk);

    for (int i = 4; i < len; i += 4) {
        for (int j = 0; j < 4; ++j)
            plain[i + j] ^= plain[i - 4 + j];
        block_crypt(plain + i, rk);
    }
}

/*n = NBlocks(C, b)
 *(P_1 = SM4Decrypt(C_1, K) xor IV
 *for i = 2 to n
 *  P_i = SM4Decrypt(C_i, K) xor C_{i - 1}
 *end for
 *P = P_1 || ... || P_n
 * */

// len represent the number of bytes of plain, rk represent round keys
void SM4::decrypt_cbc(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {

    uint32_t lastblock[4];
    //memcpy(lastblock, chiper, 16);
    for (int i = 0; i < 4; ++i)
        lastblock[i] = chiper[i];

    block_crypt(plain, rk);
    for (int i = 0; i < 4; ++i)
        plain[i] ^= IV[i];

    for (int i = 0; i < len; i += 4) {
        // if not first block
        if (i != 0)
            for (int j = 0; j < 4; ++j) {
                IV[j] = lastblock[j];
                lastblock[j] = chiper[i + j];
            }

        block_crypt(chiper + i, rk);

        for (int j = 0; j < 4; ++j)
            chiper[i + j] ^= IV[i];
    }

}


// segment size is 128
void SM4::encrypt_cfb(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j)
            IV[j] = plain[i + j] ^= IV[j];
    }
}
// segment size is 128
void SM4::decrypt_cfb(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j) {
            // let IV store chiper[i ~ i + 4]
            swap(chiper[i + j], IV[j]);
            chiper[i + j] ^= IV[j];
        }
    }
}

void SM4::encrypt_ofb(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j)
            plain[i + j] ^= IV[j];
    }
}

void SM4::decrypt_ofb(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j)
            chiper[i + j] ^= IV[j];
    }
}

void SM4::encrypt_ctr(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    IV[2] = IV[3] = 0;
    for (int i = 0; i < len; i += 4) {
        if (IV[3] == 0xffffffff) {
            IV[2]++, IV[3] = 0;
        } else {
            IV[3]++;
        }
        block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j){
            plain[i + j] ^= IV[j];
        }
    }

}

void SM4::decrypt_ctr(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {
    IV[2] = IV[3] = 0;
    for (int i = 0; i < len; i += 4) {
        if (IV[3] == 0xffffffff) {
            IV[2]++, IV[3] = 0;
        } else {
            IV[3]++;
        }
        block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j){
            chiper[i + j] ^= IV[j];
        }
    }
}
