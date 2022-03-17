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
int to_encrypt_by_rle(const uint symbs_am, const uint bits_in_rle_am, std::string input,std::string&output,std::vector<int>&rle_encryp_cnf)
{
   //Заполнение конфигурационного массива для возможности декодирования
   rle_encryp_cnf.push_back(symbs_am);
   rle_encryp_cnf.push_back(bits_in_rle_am);
   rle_encryp_cnf.push_back(0);
   while(input.size()%symbs_am!=0){
      input+="0";
      rle_encryp_cnf[2]++;
   }

   uint number_of_same_words=0;
   output="";
   std::string prev_word="";
   std::string word;
   for(uint64_t cur=0; cur<input.size();cur+=symbs_am){
       word="";
       bool is_out=false;
       //std::cout<<"Cycle 1"<<std::endl;
       //std::cout<<cur<<":"<<input.size()<<std::endl;
       for(uint64_t one_char=cur;one_char<input.size()&&one_char<symbs_am+cur;one_char++){
           word+=input[one_char];
           if(cur+symbs_am>=input.size())
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
       if(prev_word!=word||number_of_same_words==pow(2,bits_in_rle_am))
       {
          output+=prev_word;
          if(number_of_same_words<pow(2,bits_in_rle_am))
            output+=to_binary(number_of_same_words,bits_in_rle_am);
          else
            output+=to_binary(number_of_same_words-1,bits_in_rle_am);
          number_of_same_words=1;
          prev_word=word;
       }
       if(is_out){
           output+=word;
           output+=to_binary(number_of_same_words,bits_in_rle_am);
           break;
       }
   }
   /*while(output.size()%symbs_am!=0){
       output+="0";
   }*/
   std::cout<<output<<std::endl;
   std::cout<<"Bits of rle_encrypt:"<<output.size()<<std::endl;


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

int to_decode_rle(std::string encrypt_input, std::string&decode_output, std::vector<int>rle_enctypt_cnf)
{
    //while(encrypt_input.size()%rle_enctypt_cnf[0]+rle_enctypt_cnf[1]!=0){
    decode_output="";
    uint word_length = rle_enctypt_cnf[0];
    uint bits_am = rle_enctypt_cnf[1];
    uint extra_bits = rle_enctypt_cnf[2];
    for(uint cur = 0; cur+extra_bits<encrypt_input.size();cur+=word_length+bits_am){
        std::string word="";
        std::string word_am_bits="";
        uint word_am_number;
        for(uint cur_word=cur;cur_word<word_length+cur
            &&cur_word<encrypt_input.size();cur_word++){
            word+=encrypt_input[cur_word];
        }
        for(uint cur_am=cur+word_length;cur_am<cur+word_length+bits_am
            &&cur_am<encrypt_input.size();cur_am++){
            word_am_bits+=encrypt_input[cur_am];
        }
        word_am_number = bits_str_to_num(word_am_bits);
        for(uint i = 0; i<word_am_number;i++)
        {
            decode_output+=word;
        }
    }
    for(uint i = 0; i<extra_bits;i++){
        decode_output.erase(decode_output.end()-1);
    }
    std::cout<<std::endl<<"Decode RLE:"<<std::endl;
    std::cout<<decode_output<<std::endl;
    return 0;
}


uint bits_str_to_num(const std::string bits_str)
{
    uint res = 0;
    for(uint i = 0; i<bits_str.size();i++)
    {
        res*=2;
        res+=bits_str[i]-'0';
    }
    return res;
}
