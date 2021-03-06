/*
 * Tokenizador.cpp
 *
 *  Created on: 13/6/2015
 *      Author: metro
 */

#include "Tokenizador.h"
#include <iostream>

Tokenizador::Tokenizador() {
	tokens = new std::vector<std::string>();
}


void Tokenizador::tokenizar(std::string unReview){
	unsigned int i;
	char unCaracter;
	std::string palabra = std::string();

	if(!tokens->empty()) tokens->clear();

	for(i=0; i < unReview.size(); i++){
		unCaracter = unReview.at(i);
		if((unCaracter >= 'A' && unCaracter <= 'Z') || (unCaracter >= 'a' && unCaracter <= 'z') || (unCaracter >= '0' && unCaracter <= '9') || (unCaracter == '\''))
		{
			if(unCaracter != '\''){
				if(palabra.empty()) palabra = unCaracter;
				else palabra += unCaracter;
			}
		}
		else{
			if(!palabra.empty()) tokens->push_back(palabra);
			palabra.clear();
		}
	}
	if(!palabra.empty()) tokens->push_back(palabra);
	palabra.clear();
}


void Tokenizador::tokenizarConSeparador(std::string unReview, char unSeparador){
	unsigned int i;
	char unCaracter;
	std::string palabra = std::string();

	if(!tokens->empty()) tokens->clear();

	for(i=0; i < unReview.size(); i++){
		unCaracter = unReview.at(i);
		if(unCaracter != unSeparador)
		{
			if(unCaracter != '\''){
				if(palabra.empty()){
					if(unCaracter != ' ') palabra = unCaracter;
				}
				else{
					if(unCaracter == ' '){
						if((i + 1) < unReview.size()){
							if(unReview.at(i + 1) != unSeparador) palabra += unCaracter;
						}
					}
					else palabra += unCaracter;
				}
			}
		}
		else{
			if(!palabra.empty()){
				tokens->push_back(palabra);
			}
			palabra.clear();
		}
	}
	if(!palabra.empty()){
		tokens->push_back(palabra);
	}
	palabra.clear();
}



std::vector<std::string>* Tokenizador::getTokens(){
	return tokens;
}


Tokenizador::~Tokenizador() {
	delete tokens;
}

