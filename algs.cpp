#include "headers.h"
void generate_10k_symbs(){
    srand(time(NULL));
    for(int i = 0; i<global::k_10k;i++){
       global::input_data_string+= global::alphabet[rand()%global::k_dif_symbs_number];
    }
    global::input_data_string += '\0';
    set_binary_codes_for_alph();
}
void print_10k_symbs(){
    for(int i = 0; i<global::k_10k;i++){
        std::cout<<global::input_data_string[i];
    }
    return;
}
void get_one_binary_code(const char symb){
   int number = 0;
   std::string res;
   for(int i = 0; i<global::k_dif_symbs_number;i++)
   {
       if(global::alphabet[i]!=symb) number++;
       else break;
   }
   while(number!=0)
   {
       res += (number%2)+'0';
       number /=2;
   }
   for(uint i = 0; i<res.size()/2;i++){
      std::swap(res[i],res[res.size()-i-1]);
   }
   while(res.size()!=5)
       res = '0'+res;
   res+='\0';
   global::binary_codes[symb]=res;
   return;
}
void print_non_encrypt(){
    std::cout<<std::endl<<std::endl;
    std::cout<<"Non encrypt binary code:"<<std::endl;
    for(uint i = 0; i<global::non_encrypt_data.size();i++)
        std::cout<<global::non_encrypt_data[i];
    std::cout<<std::endl<<"Bits of non_encrypt: "<<global::non_encrypt_data.size()-1<<std::endl;;
    return;
}
void generate_non_encrypt(){ //bad complexity
    for(int i = 0; i<global::k_10k;i++){
        std::string temp = global::binary_codes[global::input_data_string[i]];
        for(uint i = 0; i+1<temp.size();i++){
            global::non_encrypt_data.push_back(temp[i]);
        }
    }
    global::non_encrypt_data.push_back(0);
}

void set_binary_codes_for_alph()
{
    for(int i = 0; i<global::k_dif_symbs_number;i++){
        get_one_binary_code(global::alphabet[i]);
    }
}
