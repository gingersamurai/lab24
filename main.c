#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define MAXSIZE 1024



int main(){

    token tokens[1024];
    int sz = 0;
    while (read_token(&tokens[sz])){
        sz += 1;
    }
    sz += 1;

    for(int i = 0; i < sz; i++) print_token(&tokens[i], 0);
    printf("\n");
    
}