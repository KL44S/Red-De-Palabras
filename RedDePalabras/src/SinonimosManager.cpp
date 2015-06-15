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
			tokenizador->tokenizarConSeparador(sinonimo, ',');
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
	string auxiliar;
	std::vector<std::string>* vecSinonimos;
	unsigned int cantidadDePalabras = 0;

	for(size_t i = 0; i < sinonimos.size(); i++){
		vecSinonimos = &(sinonimos.at(i));

		if(!vecSinonimos->empty()){
			for(size_t k = 0 ; k < vecSinonimos->size(); k++){
				cantidadDePalabras = 0;
				if(k == 0) sinonimo = vecSinonimos->at(0);
				else{
					sinonimoAreemplazar = vecSinonimos->at(k);
					for(size_t o = 0; o < sinonimoAreemplazar.size(); o++){
						if(sinonimoAreemplazar.at(o) == ' ') cantidadDePalabras++;
					}
					for(size_t j = 0; j < palabras->size(); j++){
						palabra = &(palabras->at(j));
						auxiliar = *palabra;
						if((j + cantidadDePalabras) < palabras->size()){
							for(size_t l = 0; l < cantidadDePalabras; l++){
								auxiliar += " " + palabras->at(j + (l + 1));
							}

						}
						if(auxiliar == sinonimoAreemplazar) {
							*palabra = sinonimo;
							if((j + cantidadDePalabras) < palabras->size()){
								for(size_t h = 0; h < cantidadDePalabras; h++){
									palabras->erase(palabras->begin() + (j + h + 1));
								}
							}
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
