#ifndef __TOKENIZER_h__
	#define __TOKENIZER_h__

	#include <string.h>
	
	#define MAX_WORD 100
	#define MAX_STR 1000

	/**
	* @PRE: Recibe una cadena.
	* @POS: Devuelve un array de cadenas con una palabra de la cadena recibida por parametro en cada cadena.
	*		La ultima posición tiene un puntero a NULL en vez de una cadena.
	**/
	char** tokenize(const char* string);

	/**
	* @PRE: Recibe un array de la forma del que devuelve la función tokenize.
	* @POS: Toda la memoria del array fue liberada.
	**/
	void destroy_token_list(char** &token_list);

#endif
