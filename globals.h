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
    extern std::map<std::string,std::string> reversed_binary_codes;
    extern std::string input_data_string; //изначальные 10к символов

    extern std::string non_encrypt_data;//некодикрованный бин. код
    extern std::string decode_data_rle;

    //0 бит - длина слова
    //1 бит - кол-во бит под число слов
    //2 бит - кол-во добавленных в конец 0
    //extern std::vector<uint>rle_cnf;

}
#endif // GLOBALS_H
