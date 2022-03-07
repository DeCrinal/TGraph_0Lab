#include"headers.h"

int get_maximum_same_symb_in_order(std::string input_str) //don't use it
{
    int max_in_order = 1;
    int temp_in_order=1;
    char prev_symb = input_str[0];
    for(uint i = 1; i <input_str.size();i++){
        if(prev_symb == input_str[i]){
            temp_in_order++;
            if(temp_in_order>max_in_order)
                max_in_order = temp_in_order;
        }
        else{
            temp_in_order = 1;
            prev_symb = input_str[i];
        }
    }
    //std::cout<<"**********Debug max:" <<max_in_order<<std::endl;
    return max_in_order; //not more than 30 bits in order (has been tested in 10e9 cases)
}

//returns result in global::std::string encrypt_data_rle
int to_encrypt_by_rle(const uint symbs_am, const std::string input)
{
   uint number_of_same_words=0;
   std::string prev_word="";
   for(uint64_t cur=0; cur<input.size();cur+=symbs_am){
       std::string word="";
       std::cout<<"Cycle 1"<<std::endl;
       std::cout<<cur<<":"<<input.size()<<std::endl;
       for(uint64_t one_char=cur;one_char<input.size()&&one_char<symbs_am+cur;one_char++){
           word+=input[one_char];
           /*std::cout<<"Cycle 2"<<std::endl;
           std::cout<<one_char<<":"<<input.size()<<std::endl;
           std::cout<<sizeof(one_char)<<std::endl;*/
       }
       std::cout<<word<<":"<<word.size()<<std::endl;
       if(prev_word=="")
           prev_word=word;
       if(prev_word==word){
           number_of_same_words++;
       }
       if(prev_word!=word||number_of_same_words==7){
          global::encrypt_data_rle+=prev_word;
          global::encrypt_data_rle+=to_binary(number_of_same_words);
          prev_word=word;
       }
   }
   std::cout<<global::encrypt_data_rle<<std::endl;
   std::cout<<"Bits of rle_encrypt:"<<global::encrypt_data_rle.size()<<std::endl;
   return 0;
}

std::string to_binary(uint number)
{
    std::string res="";
    while(number!=0){
        res+=(number%2)+'0';
        number/=2;
    }
    while(res.size()!=3){
        res+='0';
    }
    for(uint cur = 0; cur<=res.size()/2;cur++){
        std::swap(res[cur],res[res.size()-cur-1]);
    }
    return res;
}
