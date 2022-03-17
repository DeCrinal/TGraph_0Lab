#include "headers.h"
class Node{
public:
    Node*left;
    Node*right;
    int freq;
    std::string val;
    Node(){
        freq=0;
        val = "";
        left = nullptr;
        right = nullptr;
    }
};
bool cmp_nodes(Node *node1,Node* node2){
    return(node1->freq<node2->freq);
}
/*-----------------------------------Функция для получения префиксных кодов по дереву--------------------------------*/
void get_encryption(Node*node,std::string val,std::map<std::string,std::string>&haff_encrypt_cnf){
    if(node->left==nullptr || node->right==nullptr){
        if(val==""&&node->left == nullptr)
            val="0";
        std::string temporal = node->val;
        haff_encrypt_cnf[temporal]=val;
        return;
    }
    get_encryption(node->left,val+"0",haff_encrypt_cnf);
    get_encryption(node->right,val+"1",haff_encrypt_cnf);
}
void print_values(Node*node,std::string val){
   if(node->left==nullptr||node->right==nullptr)
   {
      if(val==""&&node->left == nullptr)
          val="0";
      std::cout<<node->val<<": "<<val<<std::endl;
      return;
   }
   print_values(node->left,val+"0");
   print_values(node->right,val+"1");
}
/*-----------------------------------------Функция для кодирования по Хаффману-----------------------------------------*/
int to_encrypt_by_haffman(std::string input,std::string&output,
                          std::map<std::string,std::string>&haff_encrypt_cnf, int &extra_bits)
{
    output="";
    /*Добавление символов до 5 для возможности кодирования [можно улучшить до n]*/
    while(input.size()%5!=0){
        input+="0";
        extra_bits++;
    }

    /*Составление асс.массива для количества вхождения слов*/
    std::map<std::string,int>arch;
    for(uint i = 0; i<input.size();i+=5){
      std::string next_5_bits="";
      for(uint cur=i;cur<i+5&&cur<input.size();cur++){
          next_5_bits+=input[cur];
      }
      arch[next_5_bits]++;
    }

    /*Построение дерева на массиве по частоте символов*/
    std::vector<Node*>tree;
    for(auto it = arch.begin();it!=arch.end();it++){
        Node *temp=new Node;
        temp->freq=it->second;
        temp->val=it->first;
        tree.push_back(temp);
        sort(tree.begin(),tree.end(),cmp_nodes);
    }

    /*Построение n-1 листьев для дерева по ал. Хаффмана*/
    int n = tree.size();
    for(int i = 0; i+1<n;i++){
        Node *newOne,*temp;
        newOne = new Node;
        temp = tree[0];
        tree.erase(tree.begin());
        newOne->freq+=temp->freq;
        newOne->val+=temp->val;
        newOne->left=temp;
        temp = tree[0];
        tree.erase(tree.begin());
        newOne->freq+=temp->freq;
        newOne->val+=temp->val;
        newOne->right=temp;
        tree.push_back(newOne);
        sort(tree.begin(),tree.end(),cmp_nodes);
    }
    get_encryption(tree[0],"",haff_encrypt_cnf);

    /*Кодирование входных данных по полученным данным*/
    for(unsigned int i = 0; i<input.size();i+=5){
        std::string key = "";
        for(uint cur = i; cur<i+5&&cur<input.size();cur++)
            key+=input[cur];
        output +=haff_encrypt_cnf[key];
    }
    output+="\0";
    std::cout<<"Generated prefix codes:"<<std::endl;
    print_values(tree[0],"");
    std::cout<<"Cost of coding: "<<get_cost_coding(arch,haff_encrypt_cnf)<<std::endl;
    std::cout<<output<<std::endl;
    std::cout<<std::endl<<"Bits of encrypted: "<< output.size()<<std::endl;
    return 0;
}
double get_cost_coding( std::map<std::string,int>arch, std::map<std::string,std::string>&haff_encrypt_cnf){
    double res=0;
    for(auto it = haff_encrypt_cnf.begin();it!=haff_encrypt_cnf.end();it++){
        res += (it->second.size())*(arch[it->first]/static_cast<double>(global::k_10k));
    }
    return res;
}

/*--------------------------------------Функция для декодирования к.Хаффманa----------------------------------------*/
/*Ищет вхождения слов по map, декодирует по ним; удаляет дополнительные биты*/
int to_decode_haffman(std::string input, std::string&output,
                      std::map<std::string,std::string>haff_encrypt_cnf,int extra_bits)
{
    output="";
    std::string cur_value="";
    std::map<std::string,std::string>reversed_encryption;
    for(auto it = haff_encrypt_cnf.begin();it!=haff_encrypt_cnf.end();it++){
        reversed_encryption[it->second]=it->first;
    }
    for(uint cur = 0; cur<input.size();cur++){
       cur_value += input[cur];
       if(reversed_encryption.find(cur_value)!=reversed_encryption.end()){
           output+=reversed_encryption[cur_value];
           cur_value="";
       }
    }
    while(extra_bits!=0){
        output.erase(output.end()-1);
        extra_bits--;
    }
    output+="\0";
    std::cout<<std::endl<<"Decode data:"<<std::endl;
    std::cout<<output<<std::endl;
    return 0;
}

/*Отечественный аналог bool std::string::operator==(const std::string)*/
bool is_correct_decode(const std::string str1, const std::string str2)
{
    for(uint i = 0; i<str1.size()&& i<str2.size();i++)
    {
        if(str1[i]!=str2[i])
           return false;
    }
    return true;
}
