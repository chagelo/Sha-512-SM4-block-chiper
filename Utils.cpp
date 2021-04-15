//
// Created by 19143 on 2021/4/12.
//

#include "Utils.h"

void Utils::stringtobyte(string plain, uint8_t *plainbyte, const int len) {
    for (int i = 0; i < len; i++)
        plainbyte[i] = plain[i];
    return;
}

void Utils::substr(string str, uint64_t *substr, const int pos, const int len) {
    for (int i = 0; i < len; i++) {
        substr[i / 8] = (substr[i / 8] << 8) + (uint8_t)str[pos + i];
        //rintf("%llx %llx\t", substr[i / 8], (uint8_t)str[pos + i]);
    }
    return ;
}

// initialize hash buffer, 8 64-bit registers:a,b,c,d,e,f,g,h, total 512 bits
void Utils::initializehashbuffer() {
    hashbuffer_a = 0X6A09E667F3BCC908, hashbuffer_e = 0X510E527FADE682D1;
    cout << hashbuffer_a << " " << hashbuffer_e << endl;
    hashbuffer_b = 0XBB67AE8584CAA73B, hashbuffer_f = 0X9B05688C2B3E6C1F;
    hashbuffer_c = 0X3C6EF372FE94F82B, hashbuffer_g = 0X1F83D9ABFB41BD6B;
    hashbuffer_d = 0XA54FF53A5F1D36F1, hashbuffer_h = 0X5BE0CD19137E2179;
}