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
#include <stdlib.h>

#include "stacky.h"
#include "postfixy.h"
#include "sci.h"
#include "validaciones.h"
#include "evaly.h"

void interactive_assign_variable_values();

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
                "\nSólo se admiten variables (A-Z), operadores '+','-','/','*','^','(' o ')'"
                " sin espacios y un máximo %d caracteres y mínimo 3.\n", capacity-1);

        secure_prompt("Ingrese una operación en notación infija: ", buffer, &validate_infixed_syntax);
        
        if (!perform_postfixed (buffer->raw_data, &primary, &auxiliar))
	       break;

    } while(1);
    
    printf("Resultado en notación postfija: ");
    print_stack (&primary);
    
    // Rellenamos las variables.
    fill_used(&primary);
    printf("\n===== Evaluando expresiones =====\n");

    interactive_assign_variable_values();
    reverse(&primary, &auxiliar);
    
    //printf("Expresión invertida: ");
    print_stack (&primary);
    printf ("= %lf", evaluate(&auxiliar));

    destroy_buffer(buffer);
    printf("\n");
    return 0;
}

void interactive_assign_variable_values(){
    int i;
    char var_name;
    SecuredBuffer * buffer = create_buffer(8);

    printf("\n");

    for (i=1;i<27;i++){
        if (get_variable_use()[i]){
            var_name = i+'@';

            printf("%c", var_name);
            secure_prompt("=", buffer, &validate_only_numbers);
            set_variable_value (var_name, atof(buffer->raw_data));
        }
    }

    for (i=1;i<27;i++){
        if (get_variable_use()[i]){
            var_name = i+'@';

            printf("%c=%lf\n", var_name, get_variable_value(var_name));
        }
    }

    destroy_buffer(buffer);
}