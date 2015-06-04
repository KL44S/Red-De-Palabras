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
#include <string.h>
#include <iostream>

namespace std {

class SinonimosManager {
public:
	SinonimosManager();
	void reemplazarSinonimosDe(string& unReview);
	virtual ~SinonimosManager();

private:
	std::vector< std::vector<std::string> > sinonimos;
};

} /* namespace std */

#endif /* SINONIMOSMANAGER_H_ */
