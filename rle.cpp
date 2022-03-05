#include"headers.h"

int get_maximum_same_symb_in_order(std::string input_str)
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
    return max_in_order;
}
