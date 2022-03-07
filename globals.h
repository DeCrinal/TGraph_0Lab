#ifndef GLOBALS_H
#define GLOBALS_H
#define  BINARY
#include "headers.h"
#include <iostream>
namespace global {
    extern const int k_10k;
    extern const int k_dif_symbs_number;
    extern std::string alphabet;
    extern std::map<char,std::string>	binary_codes;
#ifndef BINARY
    extern std::map<std::string,char> reversed_binary_codes;
#else
    extern std::map<std::string,std::string> reversed_binary_codes;
#endif
    extern std::string input_data_string; //изначальные 10к символов

    extern std::string non_encrypt_data;//некодикрованный бин. код

    extern std::string encrypt_data_haf;//кодированный xаффманом бин.код
    extern std::string decode_data_haf;//декодированный хaффманом символьная строка

    extern std::string encrypt_data_rle;

#ifndef BINARY
    extern std::map<char,std::string>encryption; //представление символа в кодировке
    extern std::map<char, int> arch; //количество каждого символа
#else
    extern std::map<std::string,std::string>encryption; //представление 5-ти битов в кодировке
    extern std::map<std::string, int> arch; //количество каждых 5-ти символов
#endif
}
#endif // GLOBALS_H
