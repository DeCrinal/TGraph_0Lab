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
int to_encrypt_by_rle(const uint symbs_am, const uint bits_in_rle_am, const std::string input)
{
   uint number_of_same_words=0;
   std::string prev_word="";
   std::string word;
   for(uint64_t cur=0; cur<input.size();cur+=symbs_am){
       word="";
       bool is_out=false;
       //std::cout<<"Cycle 1"<<std::endl;
       //std::cout<<cur<<":"<<input.size()<<std::endl;
       for(uint64_t one_char=cur;one_char<input.size()&&one_char<symbs_am+cur;one_char++){
           word+=input[one_char];
           if(input[one_char]=='\0')
               is_out = true;
       }
       if(cur==0)
       {
           prev_word = word;
           number_of_same_words=1;
           continue;
       }
       //std::cout<<word<<":"<<word.size()<<std::endl;
       //std::cout<<"DB, data: "<<std::endl<<global::encrypt_data_rle<<std::endl;
       if(prev_word==word){
           number_of_same_words++;
       }
       if(prev_word!=word||number_of_same_words==pow(2,bits_in_rle_am)||is_out)
       {
          global::encrypt_data_rle+=prev_word;
          if(number_of_same_words<pow(2,bits_in_rle_am))
            global::encrypt_data_rle+=to_binary(number_of_same_words,bits_in_rle_am);
          else
            global::encrypt_data_rle+=to_binary(number_of_same_words-1,bits_in_rle_am);
          number_of_same_words=1;
          prev_word=word;
       }
       if(is_out)
           break;
   }
   std::cout<<global::encrypt_data_rle<<std::endl;
   std::cout<<"Bits of rle_encrypt:"<<global::encrypt_data_rle.size()<<std::endl;

   //Заполнение конфигурационного массива для возможности декодирования
   global::rle_cnf.push_back(symbs_am);
   global::rle_cnf.push_back(bits_in_rle_am);
   global::rle_cnf.push_back(0);
   while(global::encrypt_data_rle.size()%symbs_am!=0){
      global::encrypt_data_rle.push_back(0);
      global::rle_cnf[2]++;
   }
   return 0;
}

std::string to_binary(uint number,uint bits_int_rle_am)
{
    std::string res="";
    while(number!=0){
        res+=(number%2)+'0';
        number/=2;
    }
    while(res.size()<bits_int_rle_am){
        res+='0';
    }
    for(uint cur = 0; cur<res.size()/2;cur++){
        std::swap(res[cur],res[res.size()-cur-1]);
    }
    return res;
}

int to_decode_rle(const std::string)
{
    uint word_length = global::rle_cnf[0];
    uint bits_am = global::rle_cnf[1];
    uint extra_bits = global::rle_cnf[2];
    for(uint cur = 0; cur+extra_bits<global::encrypt_data_rle.size();cur+=word_length+bits_am){
        std::string word="";
        std::string word_am_bits="";
        uint word_am_number;
        for(uint cur_word=cur;cur_word+extra_bits<word_length+cur
            &&cur_word<global::encrypt_data_rle.size();cur_word++){
            word+=global::encrypt_data_rle[cur_word];
        }
        for(uint cur_am=cur+word_length;cur_am+extra_bits<cur+word_length+bits_am
            &&cur_am<global::encrypt_data_rle.size();cur_am++){
            word_am_bits+=global::encrypt_data_rle[cur_am];
        }
        word_am_number = bits_str_to_num(word_am_bits);
        for(uint i = 0; i<word_am_number;i++)
        {
            global::decode_data_rle+=word;
        }
    }
    std::cout<<std::endl<<"Decode RLE:"<<std::endl;
    std::cout<<global::decode_data_rle<<std::endl;
    return 0;
}


uint bits_str_to_num(const std::string bits_str)
{
    uint res = 0;
    for(uint i = 0; i<bits_str.size();i++){
        res*=2;
        res+=bits_str[i]-'0';
    }
    return res;
}
