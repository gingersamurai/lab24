# Отчет по лабораторной работе N 24 по курсу
# "Фундаментальная информатика"

**студент группы:** М8О-110Б-21, Малышев Назим Бахтиярович\
**Контакты:** nazimmalyshev47@gmail.com\
**работа выполнена:** 14.05.2022\
**Преподаватель:** Никулин Сергей Петрович

## 1. Тема
Динамические структуры данных. Обработки деревьев синтаксического разбора.

## 2. Цель работы
Овладеть навыками работы с динамическими структурами и научиться обрабатывать деревья синтаксического раазбора.

## 3. Задание
сделать преобразование вида:\
 **a^(b + c) = a^b * a*c**

## 4. Оборудование 
**CPU:** Intel Core i7-8550U\
**RAM:** 8 GB\
**SSD:** 256 GB\
**MONITOR:** 2560 x 1440

## 5. Программное обеспечивание 
**Операционная система семейства:** ubuntu, **версия** 20.04 LTS\
**Интерпретатор команд:** bash, **версия** 5.0.17(1)-release.\
**Система программирования**: --, **версия**-- \
**Редактор текстов:** vs code, **версия** 1.66.1\
**Утилиты операционной системы:** --\
**Прикладные системы и программы:** --

## 6. Идея, метод, алгоритм
1. считать выражение
2. разбить каждый символ на токены для удобной обработки
3. создать бинарное дерево и в нем хранить операторы и числа
4. создать преобразователь **выражение -> дерево**
    + научиться определять приоритет операций 
    + научиться проверять вложенность скобок
5. рекурсивно трансформировать дерево (выполнение основного задания)
6. создать преобразователь **дерево -> выражение** 


# 7. Сценарий выполнения работы
1. реализация токена token.h token.c
2. реализация дерева tree.h tree.c
3. реализация преобразований
4. реализация основного файла main.c
5. настройка сборки и запуска проекта в makefile
6. тестирование
7. написание отчета 

# 8. Распечатка протокола

**main.c**
```c
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

```

**token.h**
```c
#ifndef token_h
#define token_h

typedef struct{
    // o ( ) d v F
    char type; 
    int val;
    char op_name;
    char var_name;
} token;

// узнаем приоритет оператора 
int get_priority(token *t);

// считываем токен
int read_token(token *t);

// выводим токен
void print_token(token *t);


#endif
```

**tree.h**
```c
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
```

**token.c**
```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

int get_priority(token *t){
    if (t->op_name == '+' || t->op_name == '-') {
        return 1;
    } else if (t->op_name == '*' || t->op_name == '/') {
        return 2;
    } else if (t->op_name ==  '^') {
        return 3;
    }
}

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
```

**tree.c**
```c
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
    } else if (now_node->data.type == 'd'){
        printf("%d", now_node->data.val);
    } else {
        printf("%c", now_node->data.var_name);
    }
}
```

**makefile**
```make
run : main
	./main
main : token.o tree.o main.o
	gcc main.o token.o tree.o -o main

token.o : token.c
	gcc -c token.c -o token.o

tree.o : tree.c
	gcc -c tree.c -o tree.o

main.o : main.c
	gcc -c main.c -o main.o

clean :
	rm -f main -f main.o -f token.o -f tree.o
```

### пример работы
```
gingersamurai@LY530:~/coding/lab/lab24$ make
./main
2 ^ ((a*4+(b+5))          
before transformation:
            5
        +
            b
    +
            4
        *
            a
^
    2
after transformation:
            5
        ^
            2
    *
            b
        ^
            2
*
            4
        *
            a
    ^
        2
result expression:
((2^(a*4))*((2^b)*(2^5)))
gingersamurai@LY530:~/coding/lab/lab24$ make
./main
a ^  (b + c)
before transformation:
        c
    +
        b
^
    a
after transformation:
        c
    ^
        a
*
        b
    ^
        a
result expression:
((a^b)*(a^c))

```


## 9. Дневник отладки
--

## 10. Замечания автора
--
## 11. Выводы
Мной была изучена такая структура, как бинарное дерево.\
Составлена программа реализации такого дерева.\
Бинарное дерево – очень полезная структура,
которая может решать различные задачи