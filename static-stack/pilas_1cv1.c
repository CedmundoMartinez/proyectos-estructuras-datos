#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STATIC_SIZE 16

typedef char StackType;

typedef struct _Stack {
    StackType contents[STATIC_SIZE];
    int32_t top;
} Stack;

void perform_postfixed (char * buffer, Stack * primary, Stack * axuliar);

void init_stack(Stack * s);
void push (Stack * s, StackType value);
StackType pop (Stack * s);
StackType check_top (Stack * s);
int8_t is_empty (Stack * s);
void print_stack(Stack * s);

int8_t get_precedence(char op);
int8_t is_high_than_top (Stack * s, char op);
int8_t is_supported_operator (char op);
int8_t is_variable (char var);

int main(int argc, char **argv){
    
    char buffer[STATIC_SIZE];
    buffer[STATIC_SIZE-1] = 0;
    
    Stack primary;
    Stack auxiliar;
    
    init_stack (&primary);
    init_stack (&auxiliar);
    
    printf("Programa para convertir a notación postfija.\n");
    printf("Ingrese una operación en notación normal (no más de %d caracteres): ", STATIC_SIZE);
    
    do {
        scanf("%s", buffer);
        
        if (strlen(buffer) > STATIC_SIZE - 1){
            printf("La cadena debe tener una longitud menor o igual a quince caracteres.\n");
        }else{
            break;
        }
    } while (1);
    
    perform_postfixed (buffer, &primary, &auxiliar);
    
    printf("\nLa pila: ");
    print_stack (&primary);
    
    printf("\n");
    return 0;
}

int8_t is_empty(Stack * s){
    return s->top == -1;
}

StackType check_top (Stack * s){
    return s->contents[s->top];
}

void push (Stack * s, StackType value){
    s->top++;
    s->contents[s->top] = value;
}

StackType pop(Stack * s){
    StackType v = s->contents[s->top];
    s->top--;
    return v;
}

void init_stack (Stack * s){
    s->top = -1;
}

void perform_postfixed (char * buffer, Stack * primary, Stack * auxiliar) {
    int i;
    char cur;
    
    for (i = 0; i < strlen(buffer); i++ ){
        cur = toupper(buffer[i]);
        //printf ("-------------------------------------\nEvaluando: %c\n", cur);
        
        if ( is_variable(cur) ){
            //printf ("Es variable, ingresando directamente\n");
            push (primary, cur);
            
        }else if ( is_supported_operator (cur) ){
            //printf ("Es un operador.\n");
            
            if (is_empty (auxiliar)){
                //printf ("Auxiliar esta vacia, insertando en auxiliar.\n");
                push (auxiliar, cur);
                //print_stack(auxiliar);
                //printf ("\n");
            }else{
                if (is_high_than_top(auxiliar, cur)){
                    //printf ("Tiene mayor precedencia, apliando en auxiliar\n");
                    push (auxiliar, cur);
                    
                } else {
                    //printf ("No tiene mayor precedencia.\n");
                    
                    while (  !is_high_than_top(auxiliar, cur) && !is_empty(auxiliar)){
                        push (primary, pop(auxiliar));
                    }
                    
                    push(auxiliar, cur);
                }
            }
            
        }else{
            //printf("No se ha ingresado un caracter válido.\n");
            exit(0);
        }
    }
    
    while (!is_empty(auxiliar)) {
        push(primary, pop(auxiliar));
    }
}

void print_stack (Stack * s){
    int i;
    for (i=0;i<s->top+1;i++){
        printf("|%c", s->contents[i]);
    }
}

int8_t get_precedence(char op){
    int prec;
    
    switch(op){
        case '^': prec = 2; break;
        case '*': prec = 1; break;
        case '/': prec = 1; break;
        case '+': prec = 0; break;
        case '-': prec = 0; break;
    }
    
    return prec;
}

int8_t is_supported_operator (char op) {
    int8_t is_sup = op == '+' || op == '-' || op == '^' || op == '/' || op == '*';
    if (!is_sup){
        printf("Advertencia: el operador '%c' es invalido.\n", op);
    }
    return is_sup;
}

int8_t is_variable (char var){
    return var >= 'A' && var <= 'Z';
}

int8_t is_high_than_top (Stack * s, char op){
    int precedence_oper = get_precedence(op);
    int precedence_top = get_precedence(check_top(s));
    //printf ("%c > %c? %d\n", op, check_top(s), precedence_oper > precedence_top);
    
    return precedence_oper > precedence_top;
}
