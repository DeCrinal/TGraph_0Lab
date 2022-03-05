#include "headers.h"
int main()
{
    generate_10k_symbs();
    print_10k_symbs();
    generate_non_encrypt();
    print_non_encrypt();
    to_encrypt_by_haffman(global::input_data_string);
    std::cout<<"Cost of coding: " << get_cost_coding()<<std::endl;
    to_decode_haffman();
    if(is_correct_decode())
        std::cout<<"Correct decoding"<<std::endl;
    else
        std::cout<<"Incorrect decoding"<<std::endl;
    std::cout <<"Compression ratio: " <<static_cast<double>(global::non_encrypt_data.size())/
                global::encrypt_data_haf.size()<<std::endl;
    return get_maximum_same_symb_in_order(global::encrypt_data_haf);
}
