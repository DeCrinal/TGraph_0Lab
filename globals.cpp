#include"headers.h"
namespace global {
const int k_10k = 10000;
    const int k_dif_symbs_number=25;
    std::string input_data_string;
    std::string alphabet={'a','b','c','d','e','f','A','B','C','D','E','F',' ','0','1','2','3','4','5','6','7','8','9','&','.'};
    std::map<char,std::string>binary_codes;
    std::map<std::string,std::string>reversed_binary_codes;
    std::string non_encrypt_data;
}
