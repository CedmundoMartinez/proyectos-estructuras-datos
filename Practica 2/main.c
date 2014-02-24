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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stacky.h"
#include "postfixy.h"

int main(int argc, char **argv){
    
    char buffer[STACK_STATIC_SIZE];
    buffer[STACK_STATIC_SIZE-1] = 0;

    printf("Programa para convertir a notación postfija.\n");
    
    Stack primary;
    Stack auxiliar;

    do {
        init_stack (&primary);
        init_stack (&auxiliar);
    
        printf("Ingrese una operación en notación infija (no más de %d caracteres): ", STACK_STATIC_SIZE);
    

        do {
            scanf("%s", buffer);
        
            if (strlen(buffer) > STACK_STATIC_SIZE - 1){
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