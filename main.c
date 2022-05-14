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
    print_tree(root, 0);
    
    
    
}