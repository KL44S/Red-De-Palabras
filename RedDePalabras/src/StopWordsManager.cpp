/*
 * StopWordsManager.cpp
 *
 *  Created on: 2/6/2015
 *      Author: metro
 */

#include "StopWordsManager.h"
#include <fstream>

StopWordsManager::StopWordsManager() {
	stopWords = std::vector<std::string>();

	std::string line;
	std::ifstream myfile ("stopWords.txt");
	if (myfile.is_open()){
		while (getline(myfile,line)){
			stopWords.push_back(line);

		}
		myfile.close();
	}
	else std::cout << "no se pudo arbrir archivo de stop words" << std::endl;

}


void StopWordsManager::eliminarStopWords(std::vector<std::string>* palabras){
	std::string stopWord;
	for(size_t i = 0; i < stopWords.size(); i++){
		for(size_t j = 0; j < palabras->size(); j++){
			if(stopWords.at(i) == palabras->at(j)) palabras->erase(palabras->begin() + j);
		}
	}
	//std::cout << "string sin stop word: " << str << std::endl;
}


StopWordsManager::~StopWordsManager() {
	stopWords.clear();
}

