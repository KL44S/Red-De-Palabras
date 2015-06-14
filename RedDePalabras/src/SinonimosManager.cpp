/*
 * SinonimosManager.cpp
 *
 *  Created on: 4/6/2015
 *      Author: metro
 */

#include "SinonimosManager.h"
#include <fstream>
#include <algorithm>

namespace std {

SinonimosManager::SinonimosManager() {
	string sinonimo;
	string palabra;
	std::vector<std::string>* palabras;
	unsigned int i = 0;
	ifstream miArchivo("sinonimos.txt");
	sinonimos = std::vector< std::vector<std::string> >();
	tokenizador = new Tokenizador();

	if(miArchivo.is_open()){
		while(getline(miArchivo,sinonimo)) {
			transform(sinonimo.begin(), sinonimo.end(), sinonimo.begin(), ::tolower);
			tokenizador->tokenizar(sinonimo);
			palabras = tokenizador->getTokens();
			if(!palabras->empty()) {
				std::vector<std::string> vecSinonimos = std::vector<std::string>();
				for(i = 0; i < palabras->size(); i++){
					palabra = palabras->at(i);
					vecSinonimos.push_back(palabra);
				}
				sinonimos.push_back(vecSinonimos);
				vecSinonimos.clear();
			}
		}

		miArchivo.close();
	}
	else cout << "no se pudo abrir el archivo de sinonimos" << endl;

}

void SinonimosManager::reemplazarSinonimosDe(std::vector<std::string>* palabras){
	string sinonimo;
	string sinonimoAreemplazar;
	string* palabra;
	std::vector<std::string>* vecSinonimos;

	for(size_t i = 0; i < sinonimos.size(); i++){
		vecSinonimos = &(sinonimos.at(i));

		if(!vecSinonimos->empty()){
			for(size_t k = 0 ; k < vecSinonimos->size(); k++){
				if(k == 0) sinonimo = vecSinonimos->at(0);
				else{
					sinonimoAreemplazar = vecSinonimos->at(k);
					for(size_t j = 0; j < palabras->size(); j++){
						palabra = &(palabras->at(j));
						if(*palabra == sinonimoAreemplazar) {
							*palabra = sinonimo;
						}
					}
				}
			}
		}
	}

}

SinonimosManager::~SinonimosManager() {
	sinonimos.clear();
}

} /* namespace std */
