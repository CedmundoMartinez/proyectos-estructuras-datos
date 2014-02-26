
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

#ifndef SECURE_CONSOLE_INPUT
#define SECURE_CONSOLE_INPUT

#include <stdio.h>
#include <stdint.h>

#define K_SCI_AGAIN 0x10
#define K_SCI_BREAK 0x11
#define K_SCI_CONTINUE 0x12

typedef struct _SecuredBuffer {
	char * raw_data;
	int64_t capacity;
	int64_t size;
} SecuredBuffer;

typedef int8_t ValidationResult;
typedef ValidationResult(*ValidatorType)(const SecuredBuffer *);

// Only allocates memory for SecuredBuffer Structure (does not initialize
// buffer raw data nor its capacities.
SecuredBuffer *alloc_buffer_st();

// Allocates and initializes the structure, raw data and values.
//  Set's memory to zeroes.
SecuredBuffer *create_buffer(int64_t capacity);


// Sets secured buffer size to zero, but does not reset raw data.
void recycle(SecuredBuffer *buffer);

// Sets secured buffer size to zero AND sets raw data memory to zeroes.
void full_recycle(SecuredBuffer *buffer);

// Free raw data memory and structure.
void destroy_buffer(SecuredBuffer *buffer);

// Copies raw data from b to a if capacity of a is major or equals to b.
// If success, returns pointer to a, else returns 0.
SecuredBuffer *copy_buffer(SecuredBuffer *a, const SecuredBuffer *b);


// Returns 1 if SecuredBuffer is empty.
int8_t is_buffer_empty(const SecuredBuffer *buffer);


// Reads a string from FILE only if fits on secured buffer reference
//	or reaches char endline.
int64_t secure_read (FILE *, SecuredBuffer *, char);


// Equivalent to:
// 	printf(prompt);
// 	secure_read (stdin, buf, '\n');
int64_t secure_prompt (const char *, SecuredBuffer *, ValidatorType);

#endif