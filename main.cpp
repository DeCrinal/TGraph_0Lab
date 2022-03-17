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
    int extra_bits=0;
    std::cout<<"--------------------------------------Start solo Haffman encryption--------------------------------------"<<std::endl;
    to_encrypt_by_haffman(global::non_encrypt_data,encrypt_data,haff_encrypt_cnf,extra_bits);
    to_decode_haffman(encrypt_data, decode_data,haff_encrypt_cnf,extra_bits);
    if(is_correct_decode(global::non_encrypt_data, decode_data))
        std::cout<<"Correct decoding"<<std::endl;
    else
        std::cout<<"Incorrect decoding"<<std::endl;
    std::cout <<"Compression ratio: " <<static_cast<double>(global::non_encrypt_data.size())/
                decode_data.size()<<std::endl;
    std::cout<<"Cost of coding: " << get_cost_coding()<<std::endl;
    std::cout<<"--------------------------------------Finish solo Haffman encryption--------------------------------------"<<std::endl;

    std::cout<<"--------------------------------------Start solo RLE encryption--------------------------------------"<<std::endl;
    std::cout<<"RLE:"<<std::endl;
    std::vector<int>rle_encrypt_cnf;
    to_encrypt_by_rle(5,2,global::non_encrypt_data,encrypt_data,rle_encrypt_cnf);
    to_decode_rle(encrypt_data,decode_data,rle_encrypt_cnf);
    if(is_correct_decode(global::non_encrypt_data, decode_data)){
        std::cout<<"Correct RLE decoding"<<std::endl;
    }
    else
    {
        std::cout<<"Incorrect RLE decoding"<<std::endl;
    }
    std::cout<<"--------------------------------------Finish solo RLE enctyption--------------------------------------"<<std::endl;
    std::map<std::string,std::string>haff_encrypt_cnf_1, haff_encrypt_cnf_2;
    int extra_bits_1=0, extra_bits_2=0;
    std::vector<int>rle_encrypt_cnf_1, rle_encrypt_cnf_2;
    std::cout<<"1 encr:"<<std::endl;
    to_encrypt_by_rle(5,2,global::non_encrypt_data,encrypt_data,rle_encrypt_cnf_1);
    std::cout<<"2 encr:"<<std::endl;
    to_encrypt_by_haffman(encrypt_data,encrypt_data,haff_encrypt_cnf_1,extra_bits_1);
    std::cout<<"3 encr:"<<std::endl;
    to_encrypt_by_haffman(encrypt_data,encrypt_data,haff_encrypt_cnf_2,extra_bits_2);
    std::cout<<"4 encr:"<<std::endl;
    to_encrypt_by_rle(5,2,encrypt_data,encrypt_data,rle_encrypt_cnf_2);

    std::cout<<"1 dec:";
    to_decode_rle(encrypt_data,decode_data,rle_encrypt_cnf_2);
    std::cout<<"2 dec:";
    to_decode_haffman(decode_data,decode_data,haff_encrypt_cnf_2,extra_bits_2);
    std::cout<<"3 dec:";
    to_decode_haffman(decode_data,decode_data,haff_encrypt_cnf_1,extra_bits_1);
    std::cout<<"4 dec:";
    to_decode_rle(decode_data,decode_data,rle_encrypt_cnf_1);
    if(is_correct_decode(decode_data,global::non_encrypt_data)){
        std::cout<<"Correct total decoding"<<std::endl;
    }
    else
    {
        std::cout<<"Incorrect total decoding"<<std::endl;
    }


    return 0;
}
