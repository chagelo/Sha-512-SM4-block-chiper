cmake_minimum_required(VERSION 3.12)
project(SHA_512_SM4)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(. source_list)
add_executable(SHA_512_SM4 main.cpp const.h Sha.cpp Sha.h Utils.h Utils.cpp const.cpp const.h global_var.cpp global_var.h SM4.h SM4.cpp)