#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "tree.h"


node *create_node(){
    node *res_node = (node *) malloc(sizeof(node));
    res_node->l = NULL;
    res_node->r = NULL;
    
    return res_node;
}

void print_tree(node *now_node, int depth){
    if (now_node->r != NULL) {
        print_tree(now_node->r, depth+1);
    }
    for (int i = 0; i < depth; i++) printf("    ");
    print_token(&now_node->data);
    printf("\n");
    if (now_node->l != NULL) print_tree(now_node->l, depth+1);
}

void delete_tree(node *now_node){
    if (now_node->l != NULL) delete_tree(now_node->l);
    if (now_node->r != NULL) delete_tree(now_node->r);
    free(now_node);
}

void build_tree(node *now_node, int li, int ri, token tokens[]){
    if (ri < li) return;
    int scdep = 0;
    int mn = 1000000;
    int mnid = -1;
    for (int i = li; i <= ri; i++){
        if (tokens[i].type == '(') scdep+=1;
        else if (tokens[i].type == ')') scdep-=1;
        else if (tokens[i].type == 'o') {
            int now_p = scdep*10 + get_priority(&tokens[i]);
            if (now_p < mn) {
                mn = now_p;
                mnid = i;
            }
        }
    }
    if (mnid == -1) {
        for (int i = li; i <= ri; i++){
            if (tokens[i].type == 'd' || tokens[i].type == 'v'){
                now_node->data = tokens[i];
                break;
            }
        }
    } else {
        now_node->data = tokens[mnid];
        now_node->l = create_node();
        now_node->r = create_node();
        build_tree(now_node->l, li, mnid-1, tokens);
        build_tree(now_node->r, mnid+1, ri, tokens);
    }
    
}


void transform_tree(node *now_node){
    if (now_node->data.op_name == '^'){
        if (now_node->r->data.op_name == '+'){
            node *la = now_node->l;
            node *lb = now_node->r->l;
            node *lc = now_node->r->r;

            now_node->data.op_name = '*';

            now_node->l = create_node();
            now_node->l->data.type = 'o';
            now_node->l->data.op_name = '^';

            now_node->l->l = la;
            now_node->l->r = lb;

            
            now_node->r->data.op_name = '^';
            now_node->r->l = la;
            
        }
    }
    if (now_node->l != NULL) transform_tree(now_node->l);
    if (now_node->r != NULL) transform_tree(now_node->r);
}


void print_exp(node *now_node){
    if (now_node->data.type == 'o') {
        printf("("); 
        print_exp(now_node->l);
        printf("%c", now_node->data.op_name);
        print_exp(now_node->r);
        printf(")");
    } else {
        printf("%d", now_node->data.val);
    }
}