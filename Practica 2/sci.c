
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

#include "sci.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// typedef struct _SecuredBuffer {
// 	char * raw_data;
// 	int64_t capacity;
// 	int64_t size;
// } SecuredBuffer;

// typedef int8_t ValidationResult;
// typedef ValidationResult(*ValidatorType)(const SecuredBuffer *);

SecuredBuffer *alloc_buffer_st() {
	return (SecuredBuffer *) malloc (sizeof(SecuredBuffer));
}

SecuredBuffer *create_buffer(int64_t capacity){
	SecuredBuffer *tmp = alloc_buffer_st();
	if (tmp == NULL){
		return NULL;
	}

	tmp->capacity = capacity;
	tmp->size = 0;
	memset (tmp->raw_data, 0, sizeof(char) * capacity);

	return tmp;
}

void recycle(SecuredBuffer *buffer){
	assert (buffer != NULL);
	buffer->size = 0;
}

void full_recycle(SecuredBuffer *buffer){
	assert (buffer != NULL);
	assert (buffer->raw_data != NULL);

	buffer->size = 0;
	memset (buffer->raw_data, 0, sizeof(char) * buffer->capacity);
}

void destroy_buffer(SecuredBuffer *buffer){
	assert (buffer != NULL);
	assert (buffer->raw_data != NULL);

	free (buffer->raw_data);
	free (buffer);
}

SecuredBuffer *copy_buffer(SecuredBuffer *a, const SecuredBuffer *b){
	assert (a != NULL);
	assert (a->raw_data != NULL);

	assert (b != NULL);
	assert (b->raw_data != NULL);

	#warning Función copy_buffer aún no implementada.
	return NULL;
}

int8_t is_buffer_empty(const SecuredBuffer *buffer){
	return buffer->size == 0;
}


int64_t secure_read (FILE *file, SecuredBuffer *buffer, char endline) {
	char * p;
	char ch;

	int64_t max = buffer->capacity;
	char * buf = buffer->raw_data;

	if (fgets(buf, max, file)) { // Leemos solamente "max" numero de caracteres.
			p = strchr(buf, endline); // Buscamos el salto de linea
		if (p) {
				*p = '\0'; // Si existe el salto de linea, lo reemplazamos por nulo.
		} else { // Si no eixste salgo de línea, vaciamos el búfer
			while (((ch = getchar()) != endline)
				&& !feof(file)
				&& !ferror(file)
			);

			buf[max-1] = '\0'; // En caso de no haber fin de linea, ponemos nulo al final.
		}

		return buffer->size = strlen(buf);
	} else return buffer->size = 0;
}

int64_t secure_prompt (const char *prompt, SecuredBuffer *buffer, ValidationResult(*val)(const SecuredBuffer *) ){
	ValidationResult result;
	int64_t readbytes;

	do {
		printf("%s", prompt);

		readbytes = secure_read(stdin, buffer, '\n');
		result = (*val)(buffer);

	} while (result == K_SCI_AGAIN);

	return readbytes;
}