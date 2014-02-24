
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
 
#ifndef __STACKY_H__
#define __STACKY_H__

#include <stdint.h>

// ¿Usamos pilas dinámicas o estáticas?
#ifdef USE_DYNAMIC_STACK
  #warning Pilas dinámicas aún no implementadas.
#elif USE_HYBRID_RUNTIME
  #warning Pilas híbridas aún no implementadas.
#elif USE_STATIC_STACK
	// Si el tamaño de estáticas no está definido.
	#ifndef STACK_STATIC_SIZE
		#warning No se define STACK_STATIC_SIZE, usando tamaño predeterminado.
		#define STACK_STATIC_SIZE 16
	#endif
#endif

// Verificamos que se haya definido un tipo de pila.
#ifndef STACK_TYPE
#error No se ha definido un tipo de pila (defina STACK_TYPE).
#endif


// Devuelve el valor del tamaño definido de las pilas estáticas.
int32_t get_static_stack_capacity(){ return STACK_STATIC_SIZE; }

//
// El tipo de dato que será almacenado
//	dentro de la pila.
typedef STACK_TYPE StackType;

// Estructura para contener la pila
// 	y su cabeza; en caso de ser dinámica,
//	cotendrá punteros.
typedef struct _Stack {
    int32_t top;

#ifdef USE_STATIC_STACK
    StackType contents[STACK_STATIC_SIZE];
    int32_t capacity;

#elif USE_DYNAMIC_STACK
    #error No existe definición de Stack para un tipo dinámico.
#elif USE_HYBRID_RUNTIME
    #error No existe definición de Stack para un tipo híbrido.
#endif

} Stack;

// Solicita memoria para almacenar una pila, pero no la inicializa.
// No se usa con pilas estáticas.
Stack *alloc_stack();

// Libera la memoria usada por una pila (y sus elementos).
// No se usa con pilas estáticas.
void free_stack(Stack *s);

// Inicializa una pila (en caso de ser estática, establece la cabeza a -1)
// 	en caso de ser dinámica, inicializará la memoria.
void init_stack(Stack * s);

// Apila un valor (StackType) dentro de S.
void push (Stack * s, StackType value);

// Desapila un valor (StackType) de S.
StackType pop (Stack * s);

// Obtiene el valor de la cima de la pila sin desapilarlo.
StackType check_top (Stack * s);

// Devuelve 1 si la cabeza es igual a -1; es decir, si está vacía la pila.
int8_t is_empty (Stack * s);

// Imprime la pila en formato plano.
void print_stack(Stack * s);

#endif