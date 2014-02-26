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
#include "evaly.h"
#include "stacky.h"

#include <math.h>
#include <stdio.h>

void reverse(Stack * origin, Stack * result){

	while (!is_empty(origin)){
		push (result, pop(origin));
	}
	
}

/// AB+C*
//  ---> R = AB+
//    RC*
//    ---> R = RC*
//      R

/// ABC+*
//   ---> R = BC+
//    AR*
//    ---> R = AR*
//      R

//  A*B/C+D
//  ABCD*/+

double evaluate (Stack * expression){
	StackType operation;
	StackType right;
	StackType left;
	StackType tmp;
	tmp = 0;

	if (expression->top == 0){
		return get_variable_value(K_RESULT_VARIABLE);
	}

	left = pop(expression);
	right = pop(expression);
	operation = pop(expression);

	if( !is_variable(operation) ){
		tmp = left;
		left = right;
		right = operation;
		operation = pop(expression);
	}

	if ( !is_variable(left) || !is_variable(right) ){
		printf("Sintaxis inválida: %d", expression->top);
		return 0;
	}

	double a = get_variable_value(left);
	double b = get_variable_value(right);
	double r = 0;

	switch(operation){
	case '+': r = a + b; break;
	case '-': r = a - b; break;
	case '*': r = a * b; break;
	
	case '/': 
		if (b == 0){
			printf("División entre cero: %d", expression->top);
			return 0;
		}
		
		r = a / b; 
		break;
		
	case '^': r = pow(a, b); break;
	}

	set_variable_value(K_RESULT_VARIABLE, r);
	push(expression, K_RESULT_VARIABLE);

	if (tmp != 0)
		push(expression, tmp);

	return evaluate(expression);
}


double get_variable_value(StackType variable){
	return variables[variable - '@'];
}

void set_variable_value(StackType variable, double value){
	variables[variable - '@'] = value;
}