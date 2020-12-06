// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "Graph.h"

int main() {
    std::ifstream archivo("bitacoraACT4_3.txt");
    std::vector<std::string> list;
    std::vector<std::string> data;
    std::string tipo;
    int count=0, pos=0;

    if(archivo.is_open()) {
        getline(archivo,tipo,' ');
        int aux = stoi(tipo);

        getline(archivo,tipo);
        int aux2 = stoi(tipo);

        while(getline(archivo,tipo)) {
            std::stringstream ss(tipo);
            getline(ss,tipo);
            if(count < aux) {
                list.push_back(tipo);
            } else {
                data.push_back(tipo);
            }
            count++;
        }
    }
    Graph<std::string> graph(list,data);
    std::cout << "IP con mas ip's adyacentes" << std::endl;
    graph.repMax();

    return 0;
}