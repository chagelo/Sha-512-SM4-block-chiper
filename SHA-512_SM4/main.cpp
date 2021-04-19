#include "mainwindow.h"
#include <QApplication>
#include "SM4.h"
#include <cstring>
int main(int argc, char *argv[])
{
//    uint64_t H[8];
    uint32_t MK[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    uint32_t plain[4]= {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    uint32_t IV[4] = {0};
    uint32_t rk[32];
    SM4::keyexpand(MK, rk, 0);
//    for (int i = 0 ; i < 32; ++i)
//        printf("%x\n", rk[i]);
//   SM4::crypt_ecb(plain, 4, rk);
//    //SM4::encrypt_ofb(plain, 4, rk, IV);
//      for (int i = 0; i < 4; ++i)
//          printf("plain[%d]: %x\n", i, plain[i]);
//    memset(IV, 0, sizeof(IV));
//    SM4::keyexpand(MK, rk, 0);
//    //SM4::crypt_ecb(plain, 4, rk);
//    SM4::decrypt_ofb(plain, 4, rk, IV);
//    for (int i = 0; i < 4; ++i)
//        printf("plain[%d]: %x\n", i, plain[i]);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
