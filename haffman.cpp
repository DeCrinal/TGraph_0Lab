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
        global::encryption[temporal[0]]=val;
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
    for(unsigned int i = 0; i+1<input.size();i++){
      global::arch[input[i]]++;
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
    for(unsigned int i = 0; i<input.size();i++){
        char key = input[i];
        global::encrypt_data_haf+=global::encryption[key];
    }
    std::cout<<"Generated prefix codes:"<<std::endl;
    printValues(tree[0],"");
    std::cout<<global::encrypt_data_haf<<std::endl;
    std::cout<<std::endl<<"Bits of encrypted: "<< global::encrypt_data_haf.size()<<std::endl;
    return 0;
}
double get_cost_coding(){
    double res=0;
    for(auto it = global::encryption.begin();it!=global::encryption.end();it++){
        it++; //encryption.begin() = ""
        //std::cout<<it->second.size()<<std::endl;
        //std::cout<<global::arch[it->first]<<std::endl;
        //std::cout<<(global::arch[it->first]/static_cast<double>(global::k_10k));
        res += (it->second.size())*(global::arch[it->first]/static_cast<double>(global::k_10k));
    }
    return res;
}

int to_decode_haffman()
{
    std::string cur_value="";
    std::map<std::string,char>reversed_encryption;
    for(auto it = global::encryption.begin();it!=global::encryption.end();it++){
        reversed_encryption[it->second]=it->first;
    }
    for(uint cur = 0; cur<global::encrypt_data_haf.size();cur++){
       cur_value += global::encrypt_data_haf[cur];
       if(reversed_encryption.find(cur_value)!=reversed_encryption.end()){
           global::decode_data_haf+=reversed_encryption[cur_value];
           cur_value="";
       }
    }
    return 0;
}

bool is_correct_decode()
{
    for(uint i = 0; i<global::input_data_string.size()&&
        i<global::decode_data_haf.size();i++)
    {
        if(global::decode_data_haf[i]!=global::input_data_string[i]){
           return false;
        }
    }
    return true;
}
