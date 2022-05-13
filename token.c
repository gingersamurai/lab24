#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

int read_token(token *t){
    char c = fgetc(stdin);
    while (isspace(c)) c = fgetc(stdin);
    if (c == EOF) {
        t->type = 'F';
        return 0;
    } else if (c == '('){
        t->type = '(';
    } else if (c == ')'){
        t->type = ')';
    } else if (isdigit(c)){
        t->type = 'd';
        ungetc(c, stdin);
        scanf("%d", &t->val);
    } else if (isalpha(c)){
        t->type = 'v';
        t->var_name = c;
    } else {
        t->type = 'o';
        t->op_name = c;
    }
    return 1;
}

void print_token(token *t){
    if (t->type == 'o') printf("%c", t->op_name);
    else if (t->type == '(') printf("(");
    else if (t->type == ')') printf(")");
    else if (t->type == 'd') printf("%d", t->val);
    else if (t->type == 'v') printf("%c", t->var_name);
    else if (t->type == 'F') printf(";");
}