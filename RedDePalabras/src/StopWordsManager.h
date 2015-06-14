/*
 * StopWordsManager.h
 *
 *  Created on: 2/6/2015
 *      Author: metro
 */

#ifndef STOPWORDSMANAGER_H_
#define STOPWORDSMANAGER_H_

#include <iostream>
#include <string>
#include <vector>

class StopWordsManager {
public:
	StopWordsManager();
	void eliminarStopWords(std::vector<std::string>* palabras);
	virtual ~StopWordsManager();

private:
	std::vector<std::string> stopWords;
};

#endif /* STOPWORDSMANAGER_H_ */
