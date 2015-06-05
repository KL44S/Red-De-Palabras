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
				i = 0;
				if(palabras != NULL) {
					std::vector<std::string> vecSinonimos = std::vector<std::string>();
				while(palabras[i] != NULL){
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
					i++;
				}
				sinonimos.push_back(vecSinonimos);
				vecSinonimos.clear();
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
	std::vector<std::string>* vecSinonimos;
	std::vector<std::string> sinonimoEnDistintasFormas = std::vector<std::string>();
	std::vector<std::string> sinonimoAreemplazarEnDistintasFormas = std::vector<std::string>();
	size_t tamanio;
	size_t j;
	size_t maximo = 0;
	for(size_t i = 0; i < sinonimos.size(); i++){
		vecSinonimos = &(sinonimos.at(i));

		if(vecSinonimos->size() > 16){
			if(!sinonimoEnDistintasFormas.empty()) sinonimoEnDistintasFormas.clear();

			for(j = 0 ; j < 16; j++){
				sinonimoEnDistintasFormas.push_back(vecSinonimos->at(j));
			}

			for(size_t k = 16 ; k < (vecSinonimos->size() / 16); k++){
				maximo += 16;

				if(vecSinonimos->size() >= (maximo + 16)){
					for(j = maximo ; j < (maximo + 16); j++){
						sinonimoAreemplazarEnDistintasFormas.push_back(vecSinonimos->at(j));
					}

					for(size_t g = 0; g < sinonimoAreemplazarEnDistintasFormas.size(); g++){
						sinonimoAreemplazar = sinonimoAreemplazarEnDistintasFormas.at(g);
						tamanio = sinonimoAreemplazar.size() - 1;
						pos = unReview.find(sinonimoAreemplazar);
						sinonimo = sinonimoEnDistintasFormas.at(g);

						while (pos != -1){

							/*cout << "-----------------------POSTA-----------------------------: " << endl;
							cout << unReview << endl;
							cout << endl;
							cout << endl;*/

							unReview.replace(pos, tamanio, sinonimo);

							/*cout << "-----------------------CAMBIO-----------------------------: " << endl;
							cout << unReview << endl;
							cout << endl;
							cout << endl;*/

							pos = unReview.find(sinonimoAreemplazar);
						}
					}
				}
				if(!sinonimoAreemplazarEnDistintasFormas.empty()) sinonimoAreemplazarEnDistintasFormas.clear();
			}
		}
	}
}

SinonimosManager::~SinonimosManager() {
	sinonimos.clear();
}

} /* namespace std */
