
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
 

/*
* Programa para convertir de notación infija a postfija.
*
* Alumno: Carlos Edmundo Martínez Mendoza.
* Boleta: 2013630284.
* Grupo: 1CV1.
*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "stacky.h"
#include "postfixy.h"
#include "sci.h"

static ValidationResult validate_infixed_syntax (const SecuredBuffer *buffer){
    const char *raw = buffer->raw_data;
    const int32_t len = buffer->size;

    char curbyte, pastbyte;
    int8_t is_cur_variable, is_cur_operation;
    int64_t i;
    
    if (len > 15){
        printf("ERROR: La cadena que usted ingresó sobrepasa el límite de lectura, ingrese una operación más pequeña.\n");
        return K_SCI_AGAIN;
    }

    if (len == 0){
        printf("ERROR: Favor de ingresar una operación.\n");
        return K_SCI_AGAIN;
    }

    if (len < 3){
        printf("ERROR: Cantidad de operandos y/o operadores inferior a la mínima requerida (>2)\n");
        return K_SCI_AGAIN;
    }

    for (i=0;i<len;i++){
        curbyte = toupper(raw[i]);

        if (i > 0)
            pastbyte = toupper(raw[i-1]);
        else
            pastbyte = 0;

        is_cur_variable = is_variable(curbyte);
        is_cur_operation = is_supported_operator(curbyte);

        if (!is_cur_variable && !is_cur_operation){
            printf("ERROR: En pocisión %d ('%c'), solamente se admiten variables "
                    "(A,B,C,...,Z) y operadores +,-,/,*,^\n", i+1, curbyte);
            return K_SCI_AGAIN;
        }

        if (is_cur_variable && pastbyte != 0 && is_variable(pastbyte)){
            printf("ERROR: Error en la pocisión %ld y %ld: No puede haber dos variables juntas.\n", i, i+1);
            return K_SCI_AGAIN;
        }

        if (is_cur_operation && pastbyte != 0 && is_supported_operator(pastbyte)){
            printf("ERROR: Error en la pocisión %ld y %ld: No puede haber dos operadores juntos.\n", i, i+1);
            printf("AVISO: No se soporta el operador negativo aún.\n");
            return K_SCI_AGAIN;
        }

        if (is_cur_operation && i == 0){
            printf("ERROR: El valor ingresado puede causar una salida erronea.\n");
            return K_SCI_AGAIN;   
        }
    }

    return K_SCI_CONTINUE;
}

int main(int argc, char **argv){
    
    int32_t capacity = STACK_STATIC_SIZE;
    SecuredBuffer *buffer = create_buffer(capacity+1);

    printf("Programa para convertir a notación postfija.\n");
    
    Stack primary;
    Stack auxiliar;

    do {
        init_stack (&primary);
        init_stack (&auxiliar);
    
        printf("==== AVISO ===="
                "\nSólo se admiten variables (A-Z), operadores +,-,*,/,^,"
                " sin espacios y un máximo %d caracteres y mínimo 3.\n", capacity-1);

        secure_prompt("Ingrese una operación en notación infija: ", buffer, &validate_infixed_syntax);
        
        if (!perform_postfixed (buffer->raw_data, &primary, &auxiliar))
	       break;

    } while(1);
    
    printf("Resultado en notación postfija: ");
    print_stack (&primary);
    
    destroy_buffer(buffer);
    printf("\n");
    return 0;
}
