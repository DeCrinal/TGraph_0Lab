#ifndef RLE_H
#define RLE_H
#include"headers.h"
int get_maximum_same_symb_in_order(std::string);
int to_encrypt_by_rle(const uint, const uint, const std::string);
int to_decode_rle(const std::string);
uint bits_str_to_num(const std::string);
std::string to_binary(uint,uint);
#endif // RLE_H
