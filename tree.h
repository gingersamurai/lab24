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
node *create_node();

// печатаем дерево 
void print_tree(node *now_node, int depth);

// удаляем дерево из памяти
void delete_tree(node *now_node);

// представляем выражение в виде дерева
void build_tree(node *now_node, int li, int ri, token tokens[]);

// меняет в дереве a^(b + c) на a^b * a^c
void transform_tree(node *now_node);

// выводим дерево в виде выражения
void print_exp(node *now_node);

#endif