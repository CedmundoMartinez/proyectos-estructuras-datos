
// Copyright (c) 2014, Carlos Edmundo Martínez Mendoza 
// All rights reserved. 

// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met: 

//  * Redistributions of source code must retain the above copyright notice, 
//    this list of conditions and the following disclaimer. 
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the distribution. 
//  * Neither the name of  nor the names of its contributors may be used to 
//    endorse or promote products derived from this software without specific 
//    prior written permission. 

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE. 
 

#include "postfixy.h"
#include "stacky.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int8_t perform_postfixed (StackType * buffer, Stack * primary, Stack * auxiliar) {
    int32_t i, operation_level;
    StackType cur;
    
    operation_level = 0;
    for (i = 0; i < strlen(buffer); i++ ){
        cur = toupper(buffer[i]);
        
        if ( is_variable(cur) ){
            push (primary, cur);
        }else if ( is_priority_modifier(cur) ) {
            operation_level = modify_priority(operation_level, cur);
        }else if ( is_supported_operator (cur) ){
            
            if (is_empty (auxiliar)){
                push (auxiliar, cur);
            }else{
                if (is_high_than_top(auxiliar, cur, operation_level)){
                    push (auxiliar, cur);
                    
                } else {
                    while (  !is_high_than_top(auxiliar, cur, operation_level) && !is_empty(auxiliar)){
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

int32_t get_precedence(StackType op, int32_t nested_priority){
    int32_t prec = -1;
    
    switch(op){
        case '^': prec = nested_priority + 2; break;
        case '*': prec = nested_priority + 1; break;
        case '/': prec = nested_priority + 1; break;
        case '+': prec = nested_priority + 0; break;
        case '-': prec = nested_priority + 0; break;
    }
    
    return prec;
}

int8_t is_supported_operator (StackType op) {
    return op == '+' || op == '-' || op == '^' || op == '/' || op == '*' || op == '(' || op == ')';
}

int8_t is_variable (StackType var){
    return var >= 'A' && var <= 'Z';
}

int8_t is_high_than_top (Stack * s, StackType op, int32_t nested_priority){
    int8_t precedence_oper = get_precedence(op, nested_priority);
    int8_t precedence_top = get_precedence(check_top(s), nested_priority);
    //printf ("%c > %c? %d\n", op, check_top(s), precedence_oper > precedence_top);
    
    return precedence_oper > precedence_top;
}

int32_t modify_priority(int32_t prev, StackType op) {
    return op == '(' || op == '[' || op == '{' ? prev+1 : prev-1;
}

int8_t is_priority_modifier (StackType op){
    return op == '(' || op == ')' || op == '[' || op == ']' || op == '{' || op == '}';
}
