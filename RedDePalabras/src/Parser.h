/*
 * Parser.h
 *
 *  Created on: 3/6/2015
 *      Author: metro
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "tokenizer.h"
#include "StopWordsManager.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>
#include "Exception.h"
using namespace std;

class Parser {
public:
	Parser();
	bool setArchivo(ifstream* archivo);
	bool parsearLineaEntrenamiento();
	bool parsearLineaTest();
	int getSentimiento();
	char** getTokens();
	string getLine();
	string getLineaResultado();
	virtual ~Parser();

private:
	StopWordsManager* unStopWordsManager;
	int sentimiento;
	char** tokens;
	string line;
	ifstream* myfile;
	string lineaResultado;
};

#endif /* PARSER_H_ */
