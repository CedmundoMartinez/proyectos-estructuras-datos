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
#include "stacky.h"

//////////////////////////////////
/// Métodos de uso de memoria ///
/////////////////////////////////

void init_stack (Stack * s){
    s->top = -1;
}

Stack *alloc_stack(){
}

void free_stack(Stack *){
}

//////////////////////////////////
/// Métodos para manipulación ///
/////////////////////////////////

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

void print_stack (Stack * s){
    int i;
    for (i=0;i<s->top+1;i++){
        printf("%c", s->contents[i]);
    }
}

//////////////////////////////////