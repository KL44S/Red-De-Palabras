/*
 * SinonimosManager.h
 *
 *  Created on: 4/6/2015
 *      Author: metro
 */

#ifndef SINONIMOSMANAGER_H_
#define SINONIMOSMANAGER_H_
#include <vector>
#include <string>
#include <iostream>
#include "Tokenizador.h"

namespace std {

class SinonimosManager {
public:
	SinonimosManager();
	void reemplazarSinonimosDe(std::vector<std::string>* palabras);
	virtual ~SinonimosManager();

private:
	std::vector< std::vector<std::string> > sinonimos;
	Tokenizador* tokenizador;
};

} /* namespace std */

#endif /* SINONIMOSMANAGER_H_ */
