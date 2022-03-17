#ifndef HAFFMAN_H
#define HAFFMAN_H
#include "headers.h"
class Node;
bool cmpNodes(Node *node1,Node* node2);
void getEncription(Node*node,std::string val,std::map<std::string,std::string>&);
void printValues(Node*node,std::string val);
int to_encrypt_by_haffman(std::string input, std::string&output,std::map<std::string,std::string>&,int&);
int to_unencrypt_haffman();
int to_decode_haffman(std::string,std::string&,std::map<std::string,std::string>,int extra_bits);
double get_cost_coding();
bool is_correct_decode(const std::string, const std::string);
#endif // HAFFMAN_H
