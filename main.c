#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "tree.h"
#define MAXSIZE 1024




int main(){

    token tokens[1024];
    int sz = 0;
    while (read_token(&tokens[sz])){
        sz += 1;
    }
    sz += 1;

    node *root = create_node();
    build_tree(root, 0, sz-1, tokens);
    
    printf("before transformation:\n");
    print_tree(root, 0);

    transform_tree(root);
    
    printf("after transformation:\n");
    print_tree(root, 0);

    printf("result expression:\n");
    print_exp(root);
    printf("\n");
    
}