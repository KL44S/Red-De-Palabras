/*
 * StopWordsManager.cpp
 *
 *  Created on: 2/6/2015
 *      Author: metro
 */

#include "StopWordsManager.h"
#include <vector>

StopWordsManager::StopWordsManager() {
	stopWords = std::vector<std::string>();

	std::string line;
	std::ifstream myfile ("stopWords.txt");
	if (myfile.is_open()){
		while (getline(myfile,line)){
			stopWords.push_back(" " + line + " ");
			stopWords.push_back("," + line + " ");
			stopWords.push_back(" " + line + ",");
			stopWords.push_back("." + line + " ");
			stopWords.push_back(" " + line + ".");
			stopWords.push_back("," + line + ",");
			stopWords.push_back("." + line + ".");
			stopWords.push_back("," + line + ".");
			stopWords.push_back("." + line + ",");
			stopWords.push_back(";" + line + " ");
			stopWords.push_back(" " + line + ";");
			stopWords.push_back(";" + line + ";");
			stopWords.push_back(";" + line + ",");
			stopWords.push_back("," + line + ";");
			stopWords.push_back(";" + line + ".");
			stopWords.push_back("." + line + ";");

		}
		myfile.close();
	}
	else std::cout << "no se pudo arbrir archivo de stop words" << std::endl;

}


void StopWordsManager::eliminarStopWords(std::string& str){
	int pos;
	std::string stopWord;
	size_t tamanio;
	for(size_t i = 0; i < stopWords.size(); i++){
		stopWord = stopWords.at(i);
		tamanio = stopWord.size() - 1;
		pos = str.find(stopWord);
		while (pos != -1){
			str.erase(pos, tamanio);
			pos = str.find(stopWord);
		}
	}
	//std::cout << "string sin stop word: " << str << std::endl;
}


StopWordsManager::~StopWordsManager() {
	stopWords.clear();
}

