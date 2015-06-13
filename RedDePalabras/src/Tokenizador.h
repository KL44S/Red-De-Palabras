/*
 * Tokenizador.h
 *
 *  Created on: 13/6/2015
 *      Author: metro
 */

#ifndef TOKENIZADOR_H_
#define TOKENIZADOR_H_
#include <vector>
#include <string>

class Tokenizador {
public:
	Tokenizador();
	void tokenizar(std::string unReview);
	std::vector<std::string>* getTokens();
	virtual ~Tokenizador();

private:
	std::vector<std::string>* tokens;
};

#endif /* TOKENIZADOR_H_ */
