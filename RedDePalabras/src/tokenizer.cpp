#include "tokenizer.h"

char** resize_tokens_array(char**, int, int);


char** tokenize(const char* string){
	unsigned int i, j, k, n;
	char** tokens;
	char* token;
	
	tokens = new char*[MAX_STR];
	if(!tokens)
		return NULL;
	n = MAX_STR;
	k = 0;
	j = 0;
	for(i=0; i < strlen(string); i++){
		if((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (string[i] >= '0' && string[i] <= '9'))
		{
			if(j==0){
				token = new char[MAX_WORD];
				if(!token)
					return NULL;
			}
			token[j] = string[i];
			j++;
		}
		else if( j != 0){
			token[j] = '\0';
			tokens[k] = token;
			k++;
			if(k == n){
				tokens = resize_tokens_array(tokens, n, MAX_STR * n);
				n *= MAX_STR;
			}
			j = 0;
		}
	}
	tokens[k] = NULL;
	return tokens;
}


void destroy_token_list(char** &tokens){

	delete[] tokens;
}


char** resize_tokens_array(char** arr, int old_s, int new_s){
	char** aux;
	aux = new char*[new_s];
	memcpy(aux, arr, old_s * sizeof(char*));
	delete[] arr;
	return aux;
}
