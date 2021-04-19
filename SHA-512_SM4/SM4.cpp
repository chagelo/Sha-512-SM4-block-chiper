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

void SM4::encrypt(string pwd, string filepath, string savefile, string mode)
{

    // pwd filling and expand
    uint64_t H[8];
    Sha::process(pwd, H);



    // generate MK, mk can generate roundkeys, rk arrary
    uint32_t MK[4];
    for (int i = 0; i < 4; ++i)
        MK[i] = H[i];



    // generate roundkeys
    uint32_t rk[32];
    keyexpand(MK, rk, 0);



    // read data
    size_t len = 0;
    vector<uint8_t>plain = Utils::readfile(filepath, len);
    // TODO: uint32_t IV[4] read from file



    // padding
    size_t padding_len = 16 - len % 16;
    size_t all_len = padding_len + len;

    for (size_t i = len; i < all_len; ++i)
        plain[i] = (uint8_t)padding_len;

    assert(all_len % 4 == 0);


    uint32_t IV[4] = {0};
//    startTime = std::chrono::high_resolution_clock::now();
    switch (Utils::_stoi(mode)) {
        case ECB: crypt_ecb((uint32_t *)&plain[0], all_len / 4, rk);  break;
        case CBC:encrypt_cbc((uint32_t *)&plain[0], all_len / 4, rk, IV);  break;
        case CFB:encrypt_cfb((uint32_t *)&plain[0], all_len / 4, rk, IV);  break;
        case OFB:encrypt_ofb((uint32_t *)&plain[0], all_len / 4, rk, IV);  break;
        case CTR:encrypt_ctr((uint32_t *)&plain[0], all_len / 4, rk, IV);  break;
    }
//    endTime = std::chrono::high_resolution_clock::now();
//    x = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
//    cout << "solve time:" << x << endl;


    // write encrypted data to file
    Utils::writefile(savefile, plain, all_len);
    cout << all_len << endl;
    return;
}

void SM4::decrypt(std::string pwd, std::string filepath, std::string savefile, std::string mode)
{
    // pwd filling and expand
    uint64_t H[8];
    Sha::process(pwd, H);


    // generate MK, mk can generate roundkeys, rk arrary
    uint32_t MK[4];
    for (int i = 0; i < 4; ++i)
        MK[i] = H[i];


    // generate roundkeys
    uint32_t rk[32];
    // the decryption processes of mode cfb, ofb or ctr are also their encryption process
    // it means, for sm4, the decryption and encryption processes of mode cfb, ofb, ctr use the exact same roundkey
    if (mode == "ECB" or mode == "CBC")
        keyexpand(MK, rk, 1);
    else keyexpand(MK, rk, 0);



    // auto startTime = std::chrono::high_resolution_clock::now();
    size_t len = 0;
    std::vector<uint8_t>chiper = Utils::readfile(filepath, len);

    // auto endTime = std::chrono::high_resolution_clock::now();
    // auto x = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // cal the time of read file
    // cout << x << endl;
    // cout << len << endl;

    assert(len % 4 == 0);

    uint32_t IV[4] = {0};
    //auto startTime = std::chrono::high_resolution_clock::now();
    switch (Utils::_stoi(mode)) {
        case ECB:
            crypt_ecb((uint32_t *)&chiper[0], len / 4, rk);
            break;
        case CBC:
            decrypt_cbc((uint32_t *)&chiper[0], len / 4, rk, IV);
            break;
        case CFB:
            decrypt_cfb((uint32_t *)&chiper[0], len / 4, rk, IV);
            break;
        case OFB:
            decrypt_ofb((uint32_t *)&chiper[0], len / 4, rk, IV);
            break;
        case CTR:
            decrypt_ctr((uint32_t *)&chiper[0], len / 4, rk, IV);
            break;
    }
    // auto endTime = std::chrono::high_resolution_clock::now();
    // auto x = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // cout << x << endl;

    // for (size_t i = 0; i < len; ++i)
    //     printf("%x ", chiper[i]);
    // cout << endl;


    // split, contrary to padding
    printf("%u, %x, %x\n", len, chiper[len - 1], chiper[len - 2]);
    len -= (size_t)chiper[len - 1];
    cout << "write file size " << len << endl;
    // write decrypted data to file
    Utils::writefile(savefile, chiper, len);

    return;
}




// len represent the number of 32-bit of plain, rk represent round keys
void SM4::crypt_ecb(uint32_t *plain, const int len, uint32_t *rk) {

    for (int i = 0; i < len; i += 4) {
        SM4::block_crypt(plain + i, rk);
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

// len represent the number of 32-bit of plain, rk represent round keys
void SM4::encrypt_cbc(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    // first Input1 = IV ^ plain_1
    for (int i = 0; i < 4; ++i) {
        plain[i] ^= IV[i];
    }
    SM4::block_crypt(plain, rk);

    for (int i = 4; i < len; i += 4) {
        for (int j = 0; j < 4; ++j)
            plain[i + j] ^= plain[i - 4 + j];
        SM4::block_crypt(plain + i, rk);
    }
}

/*n = NBlocks(C, b)
 *(P_1 = SM4Decrypt(C_1, K) xor IV
 *for i = 2 to n
 *  P_i = SM4Decrypt(C_i, K) xor C_{i - 1}
 *end for
 *P = P_1 || ... || P_n
 * */

// len represent the number of 32-bit of plain, rk represent round keys
void SM4::decrypt_cbc(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {

    uint32_t lastblock[4];
    //memcpy(lastblock, chiper, 16);

    for (int i = 0; i < len; i += 4) {
        // if not first block
        for (int j = 0; j < 4; ++j) {
            if (i != 0)
                IV[j] = lastblock[j];
            lastblock[j] = chiper[i + j];
        }
        SM4::block_crypt(chiper + i, rk);

        for (int j = 0; j < 4; ++j) {
            chiper[i + j] ^= IV[j];
        }
    }

}


// segment size is 128
void SM4::encrypt_cfb(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        SM4::block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j)
            IV[j] = plain[i + j] = plain[i + j] ^ IV[j];
    }
}
// segment size is 128
void SM4::decrypt_cfb(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {


    for (int i = 0; i < len; i += 4) {
        SM4::block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j) {
            // let IV store chiper[i ~ i + 4]
            swap(chiper[i + j], IV[j]);
            chiper[i + j] ^= IV[j];
        }
    }
}

void SM4::encrypt_ofb(uint32_t *plain, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        SM4::block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j)
            plain[i + j] ^= IV[j];
    }
}

void SM4::decrypt_ofb(uint32_t *chiper, const int len, uint32_t *rk, uint32_t *IV) {
    for (int i = 0; i < len; i += 4) {
        SM4::block_crypt(IV, rk);
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
        SM4::block_crypt(IV, rk);
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
        SM4::block_crypt(IV, rk);
        for (int j = 0; j < 4; ++j){
            chiper[i + j] ^= IV[j];
        }
    }
}
