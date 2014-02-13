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
* Programa para calcular la CURP de una persona con homoclave y codigo
* de verificación emuladas.
*
* Alumno: Carlos Edmundo Martínez Mendoza.
* Boleta: 2013630284.
* Grupo: 1CV1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

	// Limit get string
	//  Obtiene una cadena de texto de forma segura.
int32_t lgets (int32_t max, char * buf);

	// Generar primer bloque.
	//	Volca el primer y quinto bloque del CURP (Nombres e iniciales) a partir de una cadena.
int generar_primer_y_quinto_bloque (char * buf, char * curp);

	// Generar el segundo bloque.
	// 	Volca el segundo bloque del CURP (Fecha de nacimiento) a partir de una cadena.
int generar_segundo_bloque (char * buf, char * curp);

	// Generar el tercer bloque.
	// 	Volca el tercer bloque de la CURP (Sexo) a partir de una cadena.
int generar_tercer_bloque (char * buf, char * curp);

	// Genera el cuarto bloque.
	// 	Volca el cuarto bloque de la CURP (Lugar de nacimiento) a partir de una candea.
int generar_cuarto_bloque (int32_t indice, char * curp);

	// Genera la homoclave y verificacion aleatoria.
int generar_quinto_bloque (char * curp);

	// Primera vocal.
	// Obtiene la primera vocal apartir de la memoria de buf.
char primera_vocal(char *buf);

	// Primera consonante.
	// Obtiene la primera consonante a partir de la memoria de buf.
char primera_consonante(char *buf);

int32_t main(){
		// Longitudes de cadena.
	const int32_t string_short_buffer_len = 6;
	const int32_t string_curp_len = 19;
	const int32_t string_buffer_len = 256;

		// Tamaños de memoria.
	const size_t curp_size = sizeof(char) * string_curp_len;
	const size_t buffer_size = sizeof(char) * string_buffer_len;
	const size_t short_buffer_size = sizeof(char) * string_short_buffer_len;

		// Generamos memoria para curp y nombre.
	char * curp = (char *) malloc (curp_size);
	char * nombre = (char *) malloc (buffer_size);
	char * fecha = (char *) malloc (buffer_size);
	char * sexo = (char *) malloc (short_buffer_size);
	int32_t estado;

	if (curp == NULL || nombre == NULL
		|| fecha == NULL || sexo == NULL){
		puts("Memoria insuficiente");
	return 1;
}

		// Inicializamos la memoria a ceros.
memset(curp, 0, curp_size);
memset(nombre, 0, buffer_size);
memset(fecha, 0, buffer_size);
memset(sexo, 0, short_buffer_size);

puts ("Programa para calcular la CURP.");
puts ("Advertencia: Para el correcto funcionamiento, no debe ingresar acentos en ningún campo.");

		// Pedimos el nombre.
do{
	puts ("Introduzca su nombre iniciando por apellido paterno (ejemplo \"Gomez Pérez Maria Antonieta\"): ");
	lgets (string_buffer_len, nombre);
}while(generar_primer_y_quinto_bloque(nombre, curp));

		// Pedimos la fecha.
do{
	puts ("Introduzca su fecha de nacimiento YYYY-MM-dd (ejemplo \"1980-09-02\" para el 2 de septiembre de 1980): ");
	lgets (string_buffer_len, fecha);
}while(generar_segundo_bloque(fecha, curp));

		// Pedimos el sexo.
do{
	puts ("Introduzca su sexo (M para mujer, H para hombre): ");
	lgets (string_short_buffer_len, sexo);
}while(generar_tercer_bloque(sexo, curp));

do{
	puts ("Seleccione su estado de nacimiento. ");
	puts (
		"1) Aguascalientes\n"
	"2) Baja california\n"
	"3) Baja california sur\n"
	"4) Campeche\n"
	"5) Chiapas\n"
	"6) Chihuahua\n"
	"7) Coahuila\n"
	"8) Colima\n"
	"9) Distrito Federal\n"
	"10) Durango\n"
	"11) Guanajuato\n"
	"12) Guerrero\n"
	"13) Hidalgo\n"
	"14) Jalisco\n"
	"15) Estado de Mexico\n"
	"16) Michoacán\n"
	"17) Morelos\n"
	"18) Nayarit\n"
	"19) Nuevo León\n"
	"20) Oaxaca\n"
	"21) Puebla\n"
	"22) Querétaro\n"
	"23) Quintana Roo\n"
	"24) San Luis Potosí\n"
	"25) Sinaloa\n"
	"26) Sonora\n"
	"27) Tabasco\n"
	"28) Tamaulipas\n"
	"29) Tlaxcala\n"
	"30) Veracruz\n"
	"31) Yucatán\n"
	"32) Zacatecas\n"
	"33) Extranjero");

	printf ("Introduzca el número de estado donde ha nacido: ");
	scanf ("%d", &estado);
}while(generar_cuarto_bloque (estado, curp));

generar_quinto_bloque(curp);
printf ("Su CURP (con homoclave y verificación simulada): %s \n", curp);

free(curp);
free(nombre);
free(fecha);
free(sexo);

return 0;
}

int32_t lgets (int32_t max, char * buf){
	char * p;
	char ch;

		if (fgets(buf, max, stdin)) { // Leemos solamente "max" numero de caracteres.
			p = strchr(buf, '\n'); // Buscamos el salto de linea
		if (p) {
				*p = '\0'; // Si existe el salto de linea, lo reemplazamos por nulo.
			} else { // Si no eixste salgo de línea, vaciamos el búfer
				while (((ch = getchar()) != '\n')
					&& !feof(stdin)
					&& !ferror(stdin)
					);

				buf[max-1] = '\0'; // En caso de no haber fin de linea, ponemos nulo al final.
				// Advertimos al usuario.
			printf("Advertencia: Entrada demasiado larga, acotado a \"%s\"", buf);
		}

		return strlen(buf);
	} else return 0;
}

char primera_vocal(char *buf){
	while ( *buf != '\0' ){
		switch ( toupper(*buf) ){
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
			return *buf;
			default:
			break;
		}
		buf++;
	}

	return '\0';
}

char primera_consonante(char *buf){
	while ( *buf != '\0' ){
		switch ( toupper(*buf) ){
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
			break;
			default:
			return *buf;
		}
		buf++;
	}

	return '\0';
}

int generar_primer_y_quinto_bloque (char * buf, char * curp){
	const char delimiter[2] = " ";
	char * token;
	char * cpy;
	size_t i;

	if (strlen(buf) < 2){
		puts ("Debe ingresar su nombre completo\n");
		return 1;
	}

	cpy = buf;
	while ( *(cpy++) != '\0' ){
		char chact = toupper(*cpy);
		if ( !(chact == ' ' || chact == '\0' || (chact >= 'A' && chact <= 'Z')) ){
			puts ("El nombre debe ser solamente texto sin acentos");
			return 1;
		}
	}	

	token = strtok(buf, delimiter); // Apellido paterno.
	if (token){
		curp[0] = toupper (token[0]); 
		curp[1] = toupper (primera_vocal(token));
		curp[13] = toupper (primera_consonante(token+1));	
	}else{
		puts ("Debe ingresar un nombre con apellido paterno");
		return 1;
	}
	token = strtok(NULL, delimiter); // Apellido materno.
	if (token){
		curp[2] = toupper (token[0]);
		curp[14] = toupper (primera_consonante(token+1));
	}else{
		puts ("Debe ingresar un nombre con apellido materno");
		return 1;
	}
	token = strtok(NULL, delimiter); // Primer Nombre.
	if (token){
		curp[3] = toupper (token[0]);
		curp[15] = toupper (primera_consonante(token+1));
	}else{
		puts ("Debe ingresar su nombre(s)");
		return 1;
	}	
	return 0;
}

int generar_segundo_bloque (char * buf, char * curp){
	if (strlen(buf) < 2){
		puts ("Debe ingresar una fecha");
		return 1;
	}
	int anno, mes, dia;
	char * anno_s, * mes_s, * dia_s;
	size_t anno_s_size = sizeof(char) * 5;
	size_t diames_s_size = sizeof(char) * 3;

	// Generamos memoria
	anno_s = (char *) malloc ( anno_s_size );
	mes_s = (char *) malloc ( diames_s_size );
	dia_s = (char *) malloc ( diames_s_size );
	// Verificamos que se haya otorgado el bloque
	
	if (anno_s == NULL || mes_s == NULL || dia_s == NULL){
		puts("Memoria insuficiente");
		return 1;
	}

	// Inicializamos la memoria a cero.
	memset(anno_s, 0, anno_s_size);
	memset(mes_s, 0, diames_s_size);
	memset(dia_s, 0, diames_s_size);

	// Copiamos los cuatro primeros del bufer caracteres a anno_s
	strncpy(anno_s, buf, sizeof(char) * 4);
		
	// Copiamos los dos caracteres en la posición 5 del bufer en mes_s
	strncpy(mes_s, buf+5, sizeof(char) * 2);
		
	// Copiamos los dos caracteres en la posición 8 del bufer en dia_s
	strncpy(dia_s, buf+8, sizeof(char) * 2);

	// Convertimos de texto a número
	anno = atoi(anno_s);
	mes = atoi(mes_s);
	dia = atoi(dia_s);
	
	// Si al menos dos campos son erroneos, entonces se manda el mensaje de error de formato.
	if ( (!anno + !mes + !dia) > 2 ){
		puts("La fecha debe tener el formato adecuado: AAAA-MM-dd, (ejemplo 1990-01-21)");
		return 1;
	}

	// Si algún dato (individualmente) es erroneo, se manda el mensaje.
	if (anno == 0){
		puts("El año debe estar formado de cuatro dígitos y mayor a cero");
		return 1;
	}

	if (mes == 0){
		puts("El mes debe ser a dos dígitos y mayor a cero, con 01=Enero, 02=Febrero...");
		return 1;
	}

	if (dia == 0){
		puts("El dia debe ser a dos dígitos y mayor a cero, ejemplo: 01, 02, 03 ... 31");
		return 1;
	}

	// es_biciesto = 1 Si el año es biciesto, 0 si no.
	int es_biciesto = anno % 4 == 0  && (anno % 100 != 0  ||  anno % 400 == 0);

	// Si el año no es biciesto y el mes es febrero, hay error si se especifican mas de 28 dias.
	if ( !es_biciesto && mes == 2 && dia > 28 ){
		printf("El año %d no es biciesto, sin embargo usted indicó una fecha de Febrero que lo requiere.\n", anno);
		return 1;
	} 

	// Ya hemos validado febrero, lo excentamos.
	if ( mes != 2 ) {

		// Si el mes es par, se esperan máximo 30 dias.
		if ( mes % 2 == 0 ){
			if ( dia > 30 ){
				printf("El mes %02d solamente tiene 30 días.\n", mes);
				return 1;
			}

		// Si el mes es impar, se esperan máximo 31 dias.
		}else {
			if ( dia > 31) {
				printf("El mes %02d solamente tiene 31 días.\n", mes);
				return 1;
			}
		}
	}

	// Copiamos los valores
	strncpy(curp+4, anno_s+2, 2 );
	strncpy(curp+6, mes_s, 2 );
	strncpy(curp+8, dia_s, 2);

	free(anno_s);
	free(mes_s);
	free(dia_s);
	return 0;
}

int generar_tercer_bloque (char *buf, char * curp){
	if (strlen(buf) == 0){
		puts ("Debe ingresar un sexo");
		return 1;
	}
		
	if ( toupper( buf[0] ) == 'H' || toupper (buf[1]) == 'M'){
		curp[10] = toupper(buf[0]);
		return 0;
	}

	puts ("Debe ingresar un sexo valido");
	return 1;
}

int generar_cuarto_bloque (int32_t indice, char * curp) {
	const char estados[32][3] = { "AS", "BC", "BS", "CC", "CS", "CH", 
	"CL", "CM", "DF", "DG", "GT", "GR", "HG",
	"JC", "MC", "MN", "MS", "NT", "NL", "OC",
	"PL", "QT", "QR", "SP", "SL", "SR", "TC",
	"TS", "TL", "VZ", "YN", "ZS" };

	if (indice < 33){
		curp[11] = estados[indice-1][0];
		curp[12] = estados[indice-1][1];
	} else if (indice == 33){
		curp[11] = 'N';
		curp[12] = 'E';
	} else {
		puts ("Debe ingresar una opción del menu.");
		return 1;
	}
		
	return 0;
}

int generar_quinto_bloque (char * curp){
	srand(time(NULL));
	char a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[random () % 36];
	char b = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[random () % 36];

	curp[16] = a;
	curp[17] = b;
		
	return 0;
}
