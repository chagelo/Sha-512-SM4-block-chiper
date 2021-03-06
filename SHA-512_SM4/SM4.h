//
// Created by 19143 on 2021/4/12.
//

#ifndef SHA_512_SM4_SM4_H
#define SHA_512_SM4_SM4_H

#include "Sha.h"
#include <fstream>
#include "mode.h"
#include <QFileInfo>

class SM4 {
private:

    // get key
    static void keyexpand(uint32_t *MK, uint32_t *rk, const int &cryptflag);

    static uint32_t non_lin_tran_tau(uint32_t X);
    static uint32_t linear_trans_L(uint32_t x);
    static uint32_t linear_trans_L2(uint32_t B);
    static uint32_t permutation_T(uint32_t B);
    static uint32_t permutation_T2(uint32_t B);
    // crypt one block
    static void block_crypt(uint32_t *plainblock, uint32_t *rk);

    // five work modes
    static void crypt_ecb(uint32_t *plain, const int len, uint32_t *rk);
    static void encrypt_cbc(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV);
    static void decrypt_cbc(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV);
    static void encrypt_cfb(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV);
    static void decrypt_cfb(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV);
    static void encrypt_ofb(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV);
    static void decrypt_ofb(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV);
    static void encrypt_ctr(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV);
    static void decrypt_ctr(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV);

    static void genIV(uint32_t *IV);
    static void readIV(uint32_t *IV);
    // static uint32_t *genIV();
    // static uint32_t *readIV();

public:

    // static void encrypt_decrypt()
    static void encrypt(string pwd, string filepath, string savefile, string mode);
    static void decrypt(string pwd, string filepath, string savefile, string mode);
};


#endif //SHA_512_SM4_SM4_H
