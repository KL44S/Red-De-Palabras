/*
 * SinonimosManager.cpp
 *
 *  Created on: 4/6/2015
 *      Author: metro
 */

#include "SinonimosManager.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>
#include "Exception.h"
#include <ctype.h>
#include <algorithm>
#include <functional>
#include "tokenizer.h"
#include <vector>

namespace std {

SinonimosManager::SinonimosManager() {
	string sinonimo;
	string palabra;
	char** palabras;
	int i = 0;
	ifstream miArchivo("sinonimos.txt");
	sinonimos = std::vector< std::vector<std::string> >();

	if(miArchivo.is_open()){
		while(getline(miArchivo,sinonimo)) {
				transform(sinonimo.begin(), sinonimo.end(), sinonimo.begin(), ::tolower);
				palabras = tokenize(sinonimo.c_str());
				if(palabras != NULL) {
					std::vector<std::string> vecSinonimos = std::vector<std::string>();

				while(palabras[i+1] != NULL){
					palabra = palabras[i];
					vecSinonimos.push_back(" " + palabra + " ");
					vecSinonimos.push_back("," + palabra + " ");
					vecSinonimos.push_back(" " + palabra + ",");
					vecSinonimos.push_back("," + palabra + ",");

					vecSinonimos.push_back("." + palabra + " ");
					vecSinonimos.push_back(" " + palabra + ".");
					vecSinonimos.push_back("." + palabra + ".");

					vecSinonimos.push_back(";" + palabra + " ");
					vecSinonimos.push_back(" " + palabra + ";");
					vecSinonimos.push_back(";" + palabra + ";");

					vecSinonimos.push_back(";" + palabra + ",");
					vecSinonimos.push_back("," + palabra + ";");
					vecSinonimos.push_back(";" + palabra + ".");
					vecSinonimos.push_back("." + palabra + ";");
					vecSinonimos.push_back("." + palabra + ",");
					vecSinonimos.push_back("," + palabra + ".");
					sinonimos.push_back(vecSinonimos);
				}
				if(palabras != NULL) destroy_token_list(palabras);
			}
		}

		miArchivo.close();
	}
	else cout << "no se pudo abrir el archivo de sinonimos" << endl;

}

void SinonimosManager::reemplazarSinonimosDe(string& unReview){
	int pos;
	string sinonimo;
	string sinonimoAreemplazar;
	std::vector<std::string> vecSinonimos;
	size_t tamanio;

	for(size_t i = 0; i < sinonimos.size(); i++){
		vecSinonimos = sinonimos.at(i);
		if(!vecSinonimos.size() > 1){
			sinonimo = vecSinonimos.at(0);
			for(size_t j = 1 ; j < vecSinonimos.size(); j++){
				sinonimoAreemplazar = vecSinonimos.at(j);
				tamanio = sinonimoAreemplazar.size() - 1;
				pos = unReview.find(sinonimoAreemplazar);
				while (pos != -1){
					unReview.replace(pos, tamanio, sinonimo);
					pos = unReview.find(sinonimoAreemplazar);
				}
			}
		}
	}
}

SinonimosManager::~SinonimosManager() {
	sinonimos.clear();
}

} /* namespace std */
