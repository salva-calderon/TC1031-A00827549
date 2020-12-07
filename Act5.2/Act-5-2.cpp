// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <vector>
#include <string>

#include "HashT.h"
#include "Graph.h"

int main() {
	std::ifstream archivo("bitacoraACT4_3.txt");
	std::vector<std::vector<std::string>> data;
	int aux, aux2;
	std::string str;

	archivo >> aux >> aux2;

	for(int i=0; i<aux; i++) {
		archivo >> str;
	}

	std::getline(archivo, str);
	
	for(int i=0; i<aux2; i++) {
		std::getline(archivo,str);
		size_t pos = -1;
		std::vector<std::string> vec;
		while(str.find(' ',pos+1) != std::string::npos) {
			std::string value = str.substr(pos+1,str.find(' ',pos+1)-pos-1);
			vec.push_back(value);
			pos = str.find(' ', pos+1);
		}

		vec.push_back(str.substr(pos+1,str.size()-pos-1));
		std::vector<std::string> aux;
		aux.push_back(vec[3].substr(0,(int)vec[3].size()-5));
		aux.push_back(vec[4].substr(0,(int)vec[4].size()-5));
		data.push_back(aux);
	}

	archivo.close();
	Graph<std::string> graph(data);
	bool flag = true;

	while (flag) {
		std::cout << "Ingresa una IP: ";
		std::cin >> str;
		graph.print(str);
		std::cout << std::endl;
		std::cout << "Deseas continuar" << std::endl;
		std::cout << "(1) Si" << std::endl << "(0) No" << std::endl << "Opcion: ";
		std::cin >> flag;
		std::cout << std::endl;
	}

	return 0;
}