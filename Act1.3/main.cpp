// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549
// Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const vector<string> MESES = {
	"invalido",
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

// Funcion que convierte de string a entero los meses
int stoi_mes(const string &mes) {
	for (int i = 0; i < MESES.size(); ++i) {
		if (mes == MESES[i]) {
			return i;
		}
	}
	return 0;
}

// Funcion que convierte de entero a string los meses
string itos_mes(const int &mes) {
	if (1 <= mes && mes <= 12) {
		return MESES[mes];
	}
	return MESES[0];
}

struct Fecha {
	int mes;
	int dia;
	string hora;
	Fecha() {}
	Fecha(const int &mes, const int &dia, const string &hora) : mes(mes), dia(dia), hora(hora) {}
	friend ostream & operator<<(ostream& salida, const Fecha &fecha){
		salida << itos_mes(fecha.mes) << ' ' << fecha.dia << ' ' << fecha.hora;
		return salida;
	}
	bool operator<(const Fecha &fecha) {
		if (this -> mes < fecha.mes) {
			return true;
		} else {
			if (this -> mes == fecha.mes) {
				if (this -> dia < fecha.dia) {
					return true;
				} else {
					if (this -> dia == fecha.dia) {
						return this -> hora < fecha.hora;
					} else {
						return false;
					}
				}
			} else {
				return false;
			}
		}
	}
	bool operator==(const Fecha &fecha) {
		return (this -> mes == fecha.mes && this -> dia == fecha.dia && this -> hora == fecha.hora);
	}
	bool operator>(const Fecha &fecha) {
		return !(*this < fecha || *this == fecha);
	}
};

struct Info {
	Fecha fecha;
	string ip;
	string falla;
	Info() {}
	Info(const Fecha &fecha, const string &ip, const string &falla) : fecha(fecha), ip(ip), falla(falla) {}
	friend ostream & operator<<(ostream &salida, const Info &info){
		salida << info.fecha << ' ' << info.ip << ' ' << info.falla;
		return salida;
	}
	bool operator<(const Info &info) {
		if (this -> fecha < info.fecha) {
			return true;
		} else {
			if (this -> fecha == info.fecha) {
				if (this -> ip < info.ip) {
					return true;
				} else {
					if (this -> ip == info.ip) {
						return this -> falla < info.falla;
					} else {
						return false;
					}
				}
			} else {
				return false;
			}
		}
	}
	bool operator==(const Info &info) {
		return (this -> fecha == info.fecha && this -> ip == info.ip && this -> falla == info.falla);
	}
	bool operator<=(const Info &info) {
		return (*this < info || *this == info);
	}
};

// Algoritmo de ordenamiento merge sort
template <class T>
void mergeSort(vector<T> &vec, const int &inicio, const int &mitad, const int &fin) {
	int x = mitad - inicio + 1;
	int y = fin - mitad;
	int i, j, k;
	vector<T> A(x), B(y);

	for (i = 0; i < x; ++i) {
		A[i] = vec[inicio + i];
	}
	for (j = 0; j < y; ++j) {
		B[j] = vec[mitad + j + 1];
	}

	i = 0, j = 0, k = inicio;

	while (i < x && j < y) {
		if (A[i] <= B[j]) {
			vec[k] = A[i];
			++i;
		} else {
			vec[k] = B[j];
			++j;
		}
		++k;
	}

	while (i < x) {
		vec[k] = A[i];
		++i;
		++k;
 	}

 	while(j < y) {
 		vec[k] = B[j];
 		++j;
 		++k;
 	}
}

template <class T>
void ordenaMerge(vector<T> &vec, const int &inicio, const int &fin) {
	if (inicio < fin) {
		int mitad = inicio + (fin - inicio) / 2;
		ordenaMerge(vec, inicio, mitad);
		ordenaMerge(vec, mitad + 1, fin);

		mergeSort(vec, inicio, mitad, fin);
	}
}

// Busqueda Binaria
int busqBinaria(const vector<Info> &vec, const Fecha &tgt) {
	int inicio = 0, fin = vec.size() - 1, mitad;
	while (inicio <= fin) {
		mitad = inicio + (fin - inicio) / 2;
		if ((Fecha) (vec[mitad].fecha) == tgt) {
			return mitad;
		}
		if ((Fecha) (vec[mitad].fecha) < tgt) {
			inicio = mitad + 1;
		} else {
			fin = mitad - 1;
		}
	}
	return mitad;
}

/* Funcion que pide los rangos de fecha a los usuarios para realizar una busqueda binaria en los registros
previamente ordenados y mostrar las fechas que entren de 10 en 10 */
void menuCliente(const vector<Info> &vec) {
	Fecha rangoI, rangoF;
	string mes, hora;
	int dia, cont = 1;
	cout << "Fecha y hora de inicio" << endl
		<< "Ingresar la fecha y hora de inicio con el formato del archivo bitacora.txt (Feb 20 07:11:05)" << endl;
	cin >> mes >> dia >> hora;
	rangoI = Fecha(stoi_mes(mes), dia, hora);
	cout << "Fecha y hora final" << endl
		<< "Ingresar la fecha y hora final con el formato del archivo bitacora.txt (Feb 20 07:11:05)" << endl;
	cin >> mes >> dia >> hora;
	rangoF = Fecha(stoi_mes(mes), dia, hora);
	int inicio = busqBinaria(vec, rangoI), fin = busqBinaria(vec, rangoF);
	bool interruptor = true;
	char op;
	for (int i = inicio; i <= fin; ++i) {
		if(cont%11!=0){
			cout << vec[i] << endl;
		}
		else{
			cout << "Mostrar los siguientes elementos (S / N)?" << endl;
			cin >> op;
			if(op=='S'){
				interruptor = true;
			}
			else if(op=='N'){
				interruptor = false;
			}
		}
		cont++;
		if(interruptor == false){
			break;
		}
	}
	char aux;
	cout << "Desea realizar otra operacion (S / N)?" << endl;
	cin >> aux;
	if (aux == 'S') {
		menuCliente(vec);
	} else {
		return;
	}
}

int main() {
	vector<Info> info;
	string mes, hora, ip, falla;
	int dia;
	ifstream archivo("bitacora.txt");
	while (archivo >> mes >> dia >> hora >> ip) {
		getline(archivo, falla);
		falla.erase(falla.begin());
		// Agregar la informacion al vector
		info.push_back(Info(Fecha(stoi_mes(mes), dia, hora), ip, falla));
	}
	archivo.close();

	// Ordenar el arreglo
	ordenaMerge(info, 0, info.size() - 1);

	// Escribir el arreglo ordenado en el archivo "ordenada.txt"
	ofstream file_out("ordenada.txt");
	for (Info x : info) {
		file_out << x << endl;
	}
	file_out.close();

	// Intercatuar con el usuario
	menuCliente(info);
	
	return 0;
}