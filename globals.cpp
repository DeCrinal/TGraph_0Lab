#include"headers.h"
namespace global {
    const int k_10k = 500;
    const int k_dif_symbs_number=25;
    std::string input_data_string;
    std::string decode_data_haf;
    std::string alphabet={'a','b','c','d','e','f','A','B','C','D','E','F',' ','0','1','2','3','4','5','6','7','8','9','&','.'};
    std::map<char,std::string>binary_codes;
#ifndef BINARY
    std::map<std::string,char>reversed_binary_codes;
#else
    std::map<std::string,std::string>reversed_binary_codes;
#endif
    std::string non_encrypt_data;
    std::string encrypt_data_haf;
    std::string encrypt_data_rle;

#ifndef BINARY
    std::map<char,std::string>encryption;
    std::map<char, int> arch; //количество каждого символа
#else
    std::map<std::string,std::string>encryption;
    std::map<std::string, int> arch; //количество каждых 5-ти бит
#endif
}
