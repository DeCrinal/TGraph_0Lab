#include "headers.h"
int main()
{
    generate_10k_symbs();
    //generate_same_10k_symbs();
    print_10k_symbs();
    generate_non_encrypt();
    print_non_encrypt();
    std::string encrypt_data;
    std::string decode_data;
    std::map<std::string,std::string>haff_encrypt_cnf;
    to_encrypt_by_haffman(global::non_encrypt_data,encrypt_data,haff_encrypt_cnf);
    //to_encrypt_by_haffman(global::non_encrypt_data);
    std::cout<<"Cost of coding: " << get_cost_coding()<<std::endl;
    to_decode_haffman(encrypt_data, decode_data);
    if(is_correct_decode(global::non_encrypt_data, decode_data))
        std::cout<<"Correct decoding"<<std::endl;
    else
        std::cout<<"Incorrect decoding"<<std::endl;
    std::cout <<"Compression ratio: " <<static_cast<double>(global::non_encrypt_data.size())/
                decode_data.size()<<std::endl;

    std::cout<<"RLE:"<<std::endl;
    to_encrypt_by_rle(5,2,global::non_encrypt_data,encrypt_data);
    to_decode_rle(encrypt_data,decode_data);
    if(is_correct_decode(global::non_encrypt_data, decode_data)){
        std::cout<<"Correct RLE decoding"<<std::endl;
    }
    else
        std::cout<<"Incorrect RLE decoding"<<std::endl;

    //to_encrypt_by_haffman(global::encrypt_data_rle);
    //to_decode_haffman(global::encrypt_data_rle);
    //to_decode_rle(global::encrypt_data_rle);
    return 0;
}
