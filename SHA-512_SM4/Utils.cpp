//
// Created by 19143 on 2021/4/12.
//

#include "Utils.h"

void Utils::stringtobyte(std::string plain, uint8_t *plainbyte, const int len) {
    for (int i = 0; i < len; i++)
        plainbyte[i] = static_cast<uint8_t>(plain[i]);
    return;
}

void Utils::substr(std::string str, uint64_t *substr, const int pos, const int len) {
    for (int i = 0; i < len; i++) {
        substr[i / 8] = static_cast<uint64_t>(substr[i / 8] << 8) + static_cast<uint8_t>(str[pos + i]);
        //rintf("%llx %llx\t", substr[i / 8], (uint8_t)str[pos + i]);
    }
    return ;
}

// initialize hash buffer, 8 64-bit registers:a,b,c,d,e,f,g,h, total 512 bits
void Utils::initializehashbuffer() {
    hashbuffer_a = 0X6A09E667F3BCC908, hashbuffer_e = 0X510E527FADE682D1;
    hashbuffer_b = 0XBB67AE8584CAA73B, hashbuffer_f = 0X9B05688C2B3E6C1F;
    hashbuffer_c = 0X3C6EF372FE94F82B, hashbuffer_g = 0X1F83D9ABFB41BD6B;
    hashbuffer_d = 0XA54FF53A5F1D36F1, hashbuffer_h = 0X5BE0CD19137E2179;
}

std::vector<uint8_t> Utils::GenerateData(std::size_t bytes)
{
    std::vector<uint8_t> data(bytes);
    return data;
}

int Utils::_stoi(std::string mode)
{
    if (mode == "ECB")return 0;
    else if(mode == "CBC") return 1;
    else if(mode == "CFB")return 2;
    else if(mode == "OFB")return 3;
    else if(mode == "CTR")return 4;
}

std::vector<uint8_t> Utils::readfile(std::string path, size_t &len)
{
    // read data
    std::ifstream input(path.c_str(), std::ios::in | std::ios::binary);
    input.seekg(0, std::ios::end);
    len = input.tellg();
    input.seekg(0, std::ios::beg);

    size_t padding_len = 16 - len % 16;
    size_t all_len = len + padding_len;

    std::vector<uint8_t>plain = GenerateData(all_len + 1);

    // first write this, lost signal &
    input.read((char *)&plain[0], len);
    input.close();

    cout << "readfil size" << len << endl;

    return plain;

}

void Utils::writefile(std::string savefile, std::vector<uint8_t> data, size_t len)
{
    std::ofstream output(savefile.c_str(), std::ios::out | std::ios::binary);
    output.write((char *) &(data[0]), len);
    output.close();

    //    for (size_t i = 0; i < all_len; ++i)
    //        printf("%x ", plain[i]);
}
