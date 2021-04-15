//
// Created by 19143 on 2021/4/12.
//

#ifndef SHA_512_SM4_SM4_H
#define SHA_512_SM4_SM4_H

#include "const.h"


class SM4 {
private:

    static uint32_t non_lin_tran_tau(uint32_t X);
    static uint32_t linear_trans_L(uint32_t x);
    static uint32_t linear_trans_L2(uint32_t B);
    static uint32_t permutation_T(uint32_t B);
    static uint32_t permutation_T2(uint32_t B);

public:
    static void keyexpand(uint32_t *MK, uint32_t *rk);
};


#endif //SHA_512_SM4_SM4_H
