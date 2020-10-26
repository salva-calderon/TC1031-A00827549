// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Registro.h"
#include "Node.h"
#include "DoubleLinkedList.h"
#include "Queue.h"
#include "Heap.h"
#include "IP.h"

template<class T>
void HeapSort(DoubleLinkedList<T>& DLL, string order= "ascending") {
    Heap<T> heapAux(DLL);
    DLL.clear();
    while(!heapAux.isEmpty()) {
        if(order == "ascending") {
            DLL.addFirst(heapAux.remove());
        } else {
            DLL.addLast(heapAux.remove());
        }
    }
} 

Heap<IP> ipContador(DoubleLinkedList<Registro> &DLL) {
    Heap<IP> heapIP;
    IP aux;
    int size = DLL.getSize(), pos = 1;

    while(pos < size-1) {
        int cont = 1;
        aux.iP = DLL[pos].sIp.substr(0,DLL[pos].sIp.size()-5);
        
        while (DLL[pos].sIp.substr(0,DLL[pos].sIp.size()-5) == DLL[pos+1].sIp.substr(0,DLL[pos+1].sIp.size()-5) && pos < size-1) {
            cont++;
            pos++;
        }
        aux.cantidad = cont;
        heapIP.insert(aux);
        pos++;
    }
    return heapIP;
}

vector<string> split_istringstream(string cadena) {
    vector<string> salida;
    istringstream iss(cadena);
    string cadena2;

    while(iss >> cadena2) {
        salida.push_back(cadena2);
    }
    return salida;
}

vector<string> split(string cadena, char caracter) {

    int principio = 0;
    int ultimo = 0;
    string separacion;
    vector<string> resultados;

    while(ultimo >= 0) {
        ultimo = cadena.find(caracter, principio);
        separacion = cadena.substr(principio, ultimo - principio);
        principio = ultimo + 1;
        resultados.push_back(separacion);
    }
    return resultados;
}

void lectura(DoubleLinkedList<Registro> &registros) {
    vector<string> splitear, horaS;
    string linea = "";
    Registro temporal;
    ifstream file("bitacora2.txt");
    int cont = 0;
    while (!file.eof()) {
        getline(file,linea);
        splitear = split_istringstream(linea);
        temporal.iMes = temporal.findMes(splitear[0]);
        temporal.iDia = stoi(splitear[1]);
        horaS = split(splitear[2], ':');
        temporal.iHora = stoi(horaS[0]);
        temporal.iMin = stoi(horaS[1]);
        temporal.iSeg = stoi(horaS[2]);
        temporal.sIp = splitear[3];
        for (int i = 4; i < splitear.size(); i++) {
            temporal.sFalla += splitear[i] + " ";
        }
        temporal.calcularId(); 
        registros.addLast(temporal);
        temporal.sFalla = "";
    }
}

int main() {
    DoubleLinkedList<Registro> registros;
    Registro inicio,fin;

    int mes,dia,hora,minuto,segundo, iInicio, iFin;
    int cont = 0;
    ofstream file;

    lectura(registros);
    cout << "Se ha logrado leer el archivo. Espere unos segundos" << endl;

    HeapSort(registros);
    Heap<IP> registrosContador;
    
    registrosContador = ipContador(registros);
    
    int numero;
    cout << "Ingrese la cantidad de IPs con mayores accesos que se mostraran: ";
    cin >> numero;

    for (int i=0; i<numero; i++) {
        string output = to_string(i) +  "  " + registrosContador.remove().print();
        cout << output << endl;
    }

    return 0;
}