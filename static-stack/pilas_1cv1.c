/*
Copyright (c) 2014, Carlos Edmundo Martínez Mendoza 
All rights reserved. 

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met: 

 * Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright 
   notice, this list of conditions and the following disclaimer in the 
   documentation and/or other materials provided with the distribution. 
 * Neither the name of  nor the names of its contributors may be used to 
   endorse or promote products derived from this software without specific 
   prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE. 
 */

/*
* Programa para convertir de notación infoja a postfija.
*
* Alumno: Carlos Edmundo Martínez Mendoza.
* Boleta: 2013630284.
* Grupo: 1CV1.
*/

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

int8_t perform_postfixed (char * buffer, Stack * primary, Stack * axuliar);

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

    printf("Programa para convertir a notación postfija.\n");
    
    Stack primary;
    Stack auxiliar;

    do {
        init_stack (&primary);
        init_stack (&auxiliar);
    
        printf("Ingrese una operación en notación infija (no más de %d caracteres): ", STATIC_SIZE);
    

        do {
            scanf("%s", buffer);
        
            if (strlen(buffer) > STATIC_SIZE - 1){
                 printf("La cadena debe tener una longitud menor o igual a quince caracteres.\n");
            }else{
                 break;
            }
        } while (1);
    
        if (!perform_postfixed (buffer, &primary, &auxiliar))
	   break;

    } while(1);
    
    printf("Resultado en notación postfija: ");
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

int8_t perform_postfixed (char * buffer, Stack * primary, Stack * auxiliar) {
    int i;
    char cur;
    
    for (i = 0; i < strlen(buffer); i++ ){
        cur = toupper(buffer[i]);
        
        if ( is_variable(cur) ){
            push (primary, cur);
            
        }else if ( is_supported_operator (cur) ){
            
            if (is_empty (auxiliar)){
                push (auxiliar, cur);
            }else{
                if (is_high_than_top(auxiliar, cur)){
                    push (auxiliar, cur);
                    
                } else {
                    
                    while (  !is_high_than_top(auxiliar, cur) && !is_empty(auxiliar)){
                        push (primary, pop(auxiliar));
                    }
                    
                    push(auxiliar, cur);
                }
            }
            
        }else{
            printf("No se ha ingresado un caracter válido.\n");
            return 1;
        }
    }
    
    while (!is_empty(auxiliar)) {
        push(primary, pop(auxiliar));
    }

    return 0;
}

void print_stack (Stack * s){
    int i;
    for (i=0;i<s->top+1;i++){
        printf("%c", s->contents[i]);
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
