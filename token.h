#ifndef token_h
#define token_h

typedef struct{
    // o ( ) d v F
    char type; 
    int val;
    char op_name;
    char var_name;
} token;

// считываем токен
int read_token(token *t);

// выводим токен
void print_token(token *t);

#endif