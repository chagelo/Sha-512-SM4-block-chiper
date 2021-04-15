


#include "SM4.h"
#include <iomanip>

int main() {
    uint32_t mk[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    uint32_t rk[32];
    SM4::keyexpand(mk, rk);
    for (int i = 0; i < 32; ++i) {
        printf("%08x\n",rk[i]);
    }
}