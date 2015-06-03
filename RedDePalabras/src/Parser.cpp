/*
 * Parser.cpp
 *
 *  Created on: 3/6/2015
 *      Author: metro
 */

#include "Parser.h"
#include "StopWordsManager.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>
#include "Exception.h"
#include <ctype.h>
#include <algorithm>
#include <functional>
using namespace std;

Parser::Parser() {
	unStopWordsManager = new StopWordsManager();
}

// recive la linea con el id, sentiment y review. Devuelve review
string getReview_Entrenamiento(string str){

	int pos = str.find("_");
	pos = pos + 6;

	return str.substr(pos);
}


unsigned int getSentiment(string str){

	int pos = str.find("_");
	pos = pos + 4;

	// este asco convierte el caracter a int
	return (((int) str[pos]) - '0');
}


string getid (string str){

	int pos = str.find('\t');
	pos = pos + 6;

	return str.substr(1,pos-8);
}


string getTestReview(string str){

	int pos = str.find('\t');

	return str.substr(pos+2);
}


bool Parser::setArchivo(ifstream* archivo){
	if(myfile != NULL){
		if(myfile->is_open()){
			myfile->close();
		}
	}
	myfile = archivo;
	if (myfile->is_open()) {
		getline(*myfile,line);
		return true;
	}
	cout << "error al abrir archivo de entrenamiento" << endl;
	return false;
}


bool Parser::parsearLineaTest(){
	if(tokens != NULL) destroy_token_list(tokens);
	if(getline(*myfile,line)){
		string review = getTestReview(line);
		transform(review.begin(), review.end(), review.begin(), ::tolower);
		unStopWordsManager->eliminarStopWords(review);
		tokens = tokenize(review.c_str());
		sentimiento = getSentiment(line);
		lineaResultado = getid(line);
		return true;
	}
	return false;
}

bool Parser::parsearLineaEntrenamiento(){
	if(tokens != NULL) destroy_token_list(tokens);
	if(getline(*myfile,line)){
		string review = getReview_Entrenamiento(line);
		transform(review.begin(), review.end(), review.begin(), ::tolower);
		unStopWordsManager->eliminarStopWords(review);
		tokens = tokenize(review.c_str());
		sentimiento = getSentiment(line);
		return true;
	}
	return false;
}

int Parser::getSentimiento(){
	return sentimiento;
}

char** Parser::getTokens(){
	return tokens;
}

string Parser::getLine(){
	return line;
}

string Parser::getLineaResultado(){
	return lineaResultado;
}

Parser::~Parser() {
	if(myfile != NULL) {
		myfile->close();
	}
	if(unStopWordsManager != NULL) {
		delete unStopWordsManager;
	}
}

