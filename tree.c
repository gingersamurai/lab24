#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "tree.h"



node *create_node(token in_data){
    node *res_node = (node *) malloc(sizeof(node));
    
    res_node->data = in_data;
    res_node->l = NULL;
    res_node->r = NULL;
    
    return res_node;
}

void print_tree(node *now_node, int depth){
    if (now_node->r != NULL) {
        print_tree(now_node->r, depth+1);
    }
    for (int i = 0; i < depth; i++) printf("  ");
    print_token(&now_node->data);
    printf("\n");
}