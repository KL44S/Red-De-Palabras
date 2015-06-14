/*
 * Parser.h
 *
 *  Created on: 3/6/2015
 *      Author: metro
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "StopWordsManager.h"
#include "SinonimosManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tokenizador.h"
using namespace std;

class Parser {
public:
	Parser();
	bool setArchivo(ifstream* archivo);
	bool parsearLineaEntrenamiento();
	bool parsearLineaTest();
	int getSentimiento();
	char** getTokens();
	vector<string>* getPalabras();
	string getLine();
	string getLineaResultado();
	virtual ~Parser();

private:
	StopWordsManager* unStopWordsManager;
	SinonimosManager* sinonimosManager;
	Tokenizador* tokenizador;
	int sentimiento;
	char** tokens;
	string line;
	ifstream* myfile;
	string lineaResultado;
};

#endif /* PARSER_H_ */
