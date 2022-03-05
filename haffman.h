#ifndef HAFFMAN_H
#define HAFFMAN_H
#include "headers.h"
class Node;
bool cmpNodes(Node *node1,Node* node2);
void getEncription(Node*node,std::string val);
void printValues(Node*node,std::string val);
int to_encrypt_by_haffman(std::string input);
int to_unencrypt_haffman();
int to_decode_haffman();
double get_cost_coding();
bool is_correct_decode();
#endif // HAFFMAN_H
