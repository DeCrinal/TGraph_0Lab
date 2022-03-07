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
bool cmpNodes(Node *node1,Node* node2){
    return(node1->freq<node2->freq);
}
void getEncription(Node*node,std::string val){
    if(node->left==nullptr || node->right==nullptr){
        if(val==""&&node->left == nullptr)
            val="0";
        std::string temporal = node->val;
        //global::encryption[temporal[0]]=val;
        global::encryption[temporal]=val;
        return;
    }
    getEncription(node->left,val+"0");
    getEncription(node->right,val+"1");
}
void printValues(Node*node,std::string val){
   if(node->left==nullptr||node->right==nullptr)
   {
      if(val==""&&node->left == nullptr)
          val="0";
      std::cout<<node->val<<": "<<val<<std::endl;
      return;
   }
   printValues(node->left,val+"0");
   printValues(node->right,val+"1");
}
int to_encrypt_by_haffman(std::string input)
{
    std::string output="";
    for(uint i = 0; i+1<input.size();i+=5){

      std::string next_5_bits="";
      for(uint cur=i;cur<i+5&&cur+1<input.size();cur++){
          next_5_bits+=input[cur];
      }
      while(next_5_bits.size()!=5)
          next_5_bits="0"+next_5_bits;
      global::arch[next_5_bits]++;
    }
    std::vector<Node*>tree;
    for(auto it = global::arch.begin();it!=global::arch.end();it++){
        Node *temp=new Node;
        temp->freq=it->second;
        temp->val=it->first;
        tree.push_back(temp);
        sort(tree.begin(),tree.end(),cmpNodes);
    }
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
        sort(tree.begin(),tree.end(),cmpNodes);
    }
    getEncription(tree[0],"");
    for(unsigned int i = 0; i<input.size();i+=5){
        std::string key = "";
        for(uint cur = i; cur<i+5&&cur+1<input.size();cur++)
            key+=input[cur];
        while(key.size()!=5)
            key="0"+key;
        global::encrypt_data_haf+=global::encryption[key];
    }
    global::encrypt_data_haf+="\0";
    std::cout<<"Generated prefix codes:"<<std::endl;
    printValues(tree[0],"");
    std::cout<<global::encrypt_data_haf<<std::endl;
    std::cout<<std::endl<<"Bits of encrypted: "<< global::encrypt_data_haf.size()<<std::endl;
    return 0;
}
double get_cost_coding(){
    double res=0;
    for(auto it = global::encryption.begin();it!=global::encryption.end();it++){
        if(it==global::encryption.begin())
            it++; //encryption.begin() = ""
        res += (it->second.size())*(global::arch[it->first]/static_cast<double>(global::k_10k));
    }
    return res;
}

int to_decode_haffman(std::string &input)
{
    global::decode_data_haf="";
    std::string cur_value="";
    std::map<std::string,std::string>reversed_encryption;
    for(auto it = global::encryption.begin();it!=global::encryption.end();it++){
        reversed_encryption[it->second]=it->first;
    }
    for(uint cur = 0; cur<input.size();cur++){
       cur_value += input[cur];
       if(reversed_encryption.find(cur_value)!=reversed_encryption.end()){
           global::decode_data_haf+=reversed_encryption[cur_value];
           cur_value="";
       }
    }
    std::cout<<std::endl<<"Decode data:"<<std::endl;
    std::cout<<global::decode_data_haf<<std::endl;
    return 0;
}

bool is_correct_decode(const std::string str1, const std::string str2)
{
    for(uint i = 0; i<str1.size()&& i<str2.size();i++)
    {
        if(str1[i]!=str2[i])
           return false;
    }
    return true;
}
