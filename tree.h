#ifndef tree_h
#define tree_h

#include "token.h"
typedef struct _node node;

struct _node{
    token data;
    node *l;
    node *r;
};

// создаем вершинку
node *create_node(token in_data);

// печатаем дерево 
void print_tree(node *now_node, int depth);







#endif