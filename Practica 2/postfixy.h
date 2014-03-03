
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
 

#ifndef POSTFIXY_H
#define POSTFIXY_H

#include <stdint.h>
#include "stacky.h"

// Transorma el búfer de entrada (dado en notación infija)
// 	a una notación postfija almacenada dentro de la pila
//	primaria.
int8_t perform_postfixed (StackType * buffer, Stack * primary, Stack * axuliar);

// Obtiene el orden de precedencia del operador op.
int32_t get_precedence(StackType op, int32_t nested_priority);

// Devuelve 1 (verdadero) si OP tiene mayor precedencia que
//	la cima de la pila S. 0 (Falso) en caso contrario.
int8_t is_high_than_top (Stack * s, StackType op, int32_t nested_priority);

// Devuelve 1 (verdadero) Si el operador op está soportado.
int8_t is_supported_operator (StackType op);

// Devuelve 1 si el valor es una variable (una letra).
int8_t is_variable (StackType var);

// Devuelve 1 si el valor es un modificador de prioridad.
int8_t is_priority_modifier (StackType op);

// Devuelve la prioridad modificada dependiendo del operador.
int32_t modify_priority(int32_t prev, StackType op);
#endif