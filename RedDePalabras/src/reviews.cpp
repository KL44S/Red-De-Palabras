//============================================================================
// Name        : reviews.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Trie.hxx"
#include "Exception.h"
#include "tokenizer.h"
#include <string.h>
#include <math.h>
using namespace std;

struct nodoGrafo{
	int nPalabra;
	int ocurrencias;
};


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


// agrega una palabra al grafo y devuelve la posicion donde se agrego
int agregarPalabra(vector<list<nodoGrafo> > &grafo,ToolBox::Trie<int> &trie,
					char* palabra,int& palabras){


		list<nodoGrafo> nuevoElemento;
		grafo.push_back(nuevoElemento);
		//el tire agrega la palabra con el valor que indica la variable palabras
		trie.addEntry(palabra,strlen(palabra),palabras);

		palabras++;

		return (palabras - 1);
}

void entrenarGrafo(vector<list<nodoGrafo> >& grafo,ToolBox::Trie<int>& trie,
					char* palabra1, char* palabra2,int& palabras){

		int pos1 = trie.getEntry(palabra1,strlen(palabra1));
		if (pos1 == -1) pos1 = agregarPalabra(grafo,trie,palabra1,palabras);

		int pos2 = trie.getEntry(palabra2,strlen(palabra2));
		if (pos2 == -1) pos2 = agregarPalabra(grafo,trie,palabra2,palabras);

		// lista de palabras que aparecen despues de la palabra 1
		list<nodoGrafo> &lista = grafo.at(pos1);


		//itero entre los elementos de la lista hasta encontrar la palabra2
		bool encontrado = false;
		list<nodoGrafo>::iterator it;
		for(it = lista.begin();(it != lista.end()&& !encontrado);++it){

			if ((*it).nPalabra == pos2){
					(*it).ocurrencias++;
					encontrado = true;
			}
		}

		if(encontrado == false){
			//si no existia creo un nuevo nodo y lo agrego a la lista
			struct nodoGrafo nuevoNodo;
			nuevoNodo.nPalabra = pos2;
			nuevoNodo.ocurrencias = 1;
			lista.push_back(nuevoNodo);
		}





}

void entrenar(vector<list<nodoGrafo> >& grafo,ToolBox::Trie<int>& trie,
											char** &tokens,int& palabras){

	int i = 0;
	while(tokens[i+1] != NULL){
		entrenarGrafo(grafo,trie,tokens[i],tokens[i+1],palabras);
		i++;
	}
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

int getPesoEntrePalabras(vector<list<nodoGrafo> >& grafo,ToolBox::Trie<int>& trie,
					char* palabra1, char* palabra2){


	int peso = 0;
	int pos1 = trie.getEntry(palabra1,strlen(palabra1));
	int pos2 = trie.getEntry(palabra2,strlen(palabra2));

	// este if es positivo cuando las 2 palabras estan en el grafo
	if( (pos1 > -1) && (pos2 > -1) ){

		bool encontrado = false;
		list<nodoGrafo> &lista = grafo.at(pos1);
		list<nodoGrafo>::iterator it;
		for(it = lista.begin();it != lista.end() && !encontrado;++it){
			if ((*it).nPalabra == pos2){
				peso = (*it).ocurrencias;
				encontrado = true;
			}
		}
	}

	return peso;


}

int getPeso(vector<list<nodoGrafo> >& grafo,ToolBox::Trie<int>& trie,
											char** &tokens){

	int i = 0;
	int peso = 0;
	int actual = 0;
	int recorrido = 0;

	while(tokens[i+1] != NULL){
		actual = getPesoEntrePalabras(grafo,trie,tokens[i],tokens[i+1]);
		if(actual > 0) recorrido++;
		peso = peso + actual;
		i++;
	}


	return recorrido;
}

void eliminarStopWords(string& str){

	int pos;

	pos = str.find(" a ");
	while (pos != -1){
		str.erase(pos+1,2);
		pos = str.find(" a ");
	}

	pos = str.find(" an ");
	while (pos != -1){
		str.erase(pos+1,3);
		pos = str.find(" an ");
	}

	pos = str.find(" by ");
	while (pos != -1){
		str.erase(pos+1,3);
		pos = str.find(" by ");
	}

	pos = str.find(" in ");
	while (pos != -1){
		str.erase(pos+1,3);
		pos = str.find(" in ");
	}

	pos = str.find(" and ");
	while (pos != -1){
		str.erase(pos+1,4);
		pos = str.find(" and ");
	}

	pos = str.find(" the ");
	while (pos != -1){
		str.erase(pos+1,4);
		pos = str.find(" the ");
	}

	pos = str.find(" her ");
	while (pos != -1){
		str.erase(pos+1,4);
		pos = str.find(" her ");
	}

	pos = str.find(" his ");
	while (pos != -1){
		str.erase(pos+1,4);
		pos = str.find(" his ");
	}

}



int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!


	int procesadas = 0;
	int palabrasP = 0;
	int palabrasN = 0;

	// creo tries y grafos, positivos y negativos
	ToolBox::Trie<int> trieP(-1);
	vector<list<nodoGrafo> > grafoP;
	ToolBox::Trie<int> trieN(-1);
	vector<list<nodoGrafo> > grafoN;
	int sentimiento;

	string line;
	ifstream myfile ("labeledTrainData.tsv");
	getline(myfile,line);
	if (myfile.is_open()){

		while	(getline(myfile,line)){
			string review = getReview_Entrenamiento(line);
			transform(review.begin(), review.end(), review.begin(), ::tolower);
			eliminarStopWords(review);
			char** tokens = tokenize(review.c_str());

			sentimiento = getSentiment(line);
			if(sentimiento == 1) entrenar(grafoP,trieP,tokens,palabrasP);
			else if(sentimiento == 0) entrenar(grafoN,trieN,tokens,palabrasN);
			if((procesadas % 600) == 0) cout << procesadas <<endl;
			destroy_token_list(tokens);
			procesadas++;
		}
		myfile.close();
	}

	cout << "palabras positivas:" << palabrasP << endl;
	cout << "palabras negativas" << palabrasN << endl;

	ofstream resultfile("resultado.tsv");
	resultfile << "id,sentiment\n";

	int clasificadas = 0;
	ifstream testfile ("testData.tsv");
	getline(testfile,line);
	if (testfile.is_open()){
		while (getline(testfile,line)){
			string testReview = getTestReview(line);
			transform(testReview.begin(),testReview.end(), testReview.begin(), ::tolower);
			eliminarStopWords(testReview);
			char** tokens = tokenize(testReview.c_str());

			int pesoPositivo = getPeso(grafoP,trieP,tokens);
			int pesoNegativo = getPeso(grafoN,trieN,tokens);
			destroy_token_list(tokens);

			string lineaResultado = getid(line);
			if((pesoPositivo + 5) > pesoNegativo) lineaResultado += ",1\n";
			else lineaResultado += ",0\n";

			resultfile << lineaResultado;

			if ((clasificadas % 500) == 0) cout << clasificadas << endl;
			clasificadas ++;


		}
	}



return 0;
}
