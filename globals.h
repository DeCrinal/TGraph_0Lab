#ifndef GLOBALS_H
#define GLOBALS_H
#include "headers.h"
#include <iostream>
namespace global {
    extern const int k_10k;
    extern const int k_dif_symbs_number;
    extern std::string alphabet;
    extern std::map<char,std::string>	binary_codes;
    extern std::map<std::string,char> reversed_binary_codes;

    extern std::string input_data_string; //изначальные 10к символов

    extern std::string non_encrypt_data;//некодикрованный бин. код

    extern std::string encrypt_data_haf;//кодированный xаффманом бин.код
    extern std::string decode_data_haf;//декодированный хaффманом символьная строка

    extern std::string encrypt_data_rle;

    extern std::map<char,std::string>encryption; //представление символа в кодировке
    extern std::map<char, int> arch; //количество каждого символа
}
#endif // GLOBALS_H
