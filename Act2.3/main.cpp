// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549
// Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
	for (int i = 0; i < MESES.size(); i++) {
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


// Esctructura Fecha
struct Fecha {
	int mes;
	int dia;
	string hora;
	Fecha();
	Fecha(const int &mes, const int &dia, const string &hora);
	friend ostream & operator<<(ostream& salida, const Fecha &fecha);
	bool operator<(const Fecha &fecha);
	bool operator==(const Fecha &fecha);
	bool operator>(const Fecha &fecha);
};

Fecha::Fecha() {

}

Fecha::Fecha(const int &mes, const int &dia, const string &hora) {
    this->mes = mes;
    this->dia = dia;
    this->hora = hora;
}

ostream & operator<<(ostream& salida, const Fecha &fecha) {
    salida << itos_mes(fecha.mes) << " " << fecha.dia << " " << fecha.hora;
	return salida;
}

bool Fecha::operator<(const Fecha &fecha) {
    if (this->mes < fecha.mes) {
        return true;
    } 
    else {
        if (this->mes == fecha.mes) {
            if (this->dia < fecha.dia) {
                return true;
            } 
            else {
                if (this->dia == fecha.dia) {
                    return this->hora < fecha.hora;
                } 
                else {
                    return false;
                }
            }
        } 
        else {
            return false;
        }
    }
}

bool Fecha::operator==(const Fecha &fecha) {
	return (this->mes == fecha.mes && this->dia == fecha.dia && this->hora == fecha.hora);
}
bool Fecha::operator>(const Fecha &fecha) {
	return !(*this < fecha || *this == fecha);
}

// Esctructura Info
struct Info {
	Fecha fecha;
	string ip;
	string falla;
	Info();
	Info(const Fecha &fecha, const string &ip, const string &falla);
	friend ostream & operator<<(ostream &salida, const Info &data);
	bool operator<(const Info &data);
	bool operator==(const Info &data);
	bool operator<=(const Info &data);
};


Info::Info() {

}

Info::Info(const Fecha &fecha, const string &ip, const string &falla) {
    this->fecha = fecha;
    this-> ip = ip;
    this->falla = falla;
}

ostream & operator<<(ostream &salida, const Info &data){
    salida << data.fecha << " " << data.ip << " " << data.falla;
    return salida;
}

bool Info::operator<(const Info &data) {
    if (this->fecha < data.fecha) {
        return true;
    } 
    else {
        if (this->fecha == data.fecha) {
            if (this->ip < data.ip) {
                return true;
            } 
            else {
                if (this->ip == data.ip) {
                    return this->falla < data.falla;
                } 
                else {
                    return false;
                }
            }
        } 
        else {
            return false;
        }
    }
}

bool Info::operator==(const Info &data) {
    return (this->fecha == data.fecha && this->ip == data.ip && this->falla == data.falla);
}
bool Info::operator<=(const Info &data) {
    return (*this < data || *this == data);
}

// Esctructura Node
template <class T>
struct Node {
	T data;
	Node<T> *next;
	Node<T> *prev;
	Node(const T &data);
	Node(const T &data, Node<T> *next, Node<T> *prev);
};

template <class T>
Node<T>::Node(const T &data){
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
} 

template <class T>
Node<T>::Node(const T &data, Node<T> *next, Node<T> *prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
} 

// Clase Stack
template<class T>
class Stack {
	Node<T> *tail;
	int tam;
public:
	// Constructor por default
	Stack(void) : tail(nullptr), tam(0) {}

	// Funcion que regresa si el stack esta vacio
	bool isEmpty(void) {
		return tail == nullptr;
	}

	// Funcion que elimina el elemento indicado por el tope del stack
	T pop(void) {
		if (this->isEmpty()) {
			throw "Stack Vacio";
		}
		T valor = tail->data;
		Node<T> *aux = tail;
		tail = tail->next;
		delete aux;
		tam--;
		return valor;
	}

	// Funcion que inserta un nuevo elemento en el tope del stack
	void push(const T &elemento) {
		tail = new Node<T>(elemento, tail, nullptr);
		tam++;
	}

	// Funcion que obtiene el valor del ultimo nodo agregado al stack
	T top(void) {
		if (this->isEmpty()) {
			throw "Stack Vacio";
		}
		return tail->data;
	}

	// Funcion que regresa el tamano del stack
	int getTam(void) {
		return tam;
	}

	// Funcion que elimina todos los elementos del stack
	void clear(void) {
		while (!(this->isEmpty())) {
			this->pop();
		}
	}
};

// Clase Doubly Linked List
template<class T>
class DoublyLinkedList {
	Node<T> *head;
	Node<T> *tail;
	int tam;
public:
	// Constructor por default
	DoublyLinkedList(void) : head(nullptr), tail(nullptr), tam(0) {}

	// Funcion que regresa el tamano de la DLL
	int getTam(void) {
		return tam;
	}

	// Funcion que regresa si la DLL esta vacia
	bool isEmpty(void) {
		return tam <= 0;
	}

	// Funcion que permite acceder a un elemento de la DLL con []
	T& operator[](const int &indice) {
		if (!(1 <= indice && indice <= tam)) {
			throw out_of_range("Posicion Invalida " + to_string(indice));
		}
		auto aux = head;
		int i = 1;
		while (i++ != indice) {
			aux = aux->next;
		}
		return aux->data;
	}

	// Funcion que inserta un elemento a la DLL
	void insert(const T &elemento) {
		tail = new Node<T>(elemento, nullptr, tail);
		if (tam == 0) {
			head = tail;
		} 
		else {
			Node<T> *aux = tail;
			aux = (aux->prev);
			(aux->next) = tail;
		}
		tam++;
	}


	/* Funciones que ordenan la DLL
		- ordenaMerge
		- mergeSort
		- sort
	*/

	void ordenaMerge(const int &izq, const int &mit, const int &der) {
		int size = der - izq + 1;
		int i = izq;
		int j = mit + 1;
		int k = size - 1;
		Stack<T> stack;
		while (size--) {
			T I, J;
			if (i <= mit) {
				I = (*this)[i];
			}
			if (j <= der) {
				J = (*this)[j];
			}
			if (i <= mit && j <= der) {
				if (I < J) {
					stack.push(I);
					i++;
				} 
				else {
					stack.push(J);
					j++;
				}
			} 
			else if (i <= mit) {
				stack.push(I);
				i++;
			} 
			else {
				stack.push(J);
				j++;
			}
		}

		for (int temp = k; temp >= 0; temp--) {
			(*this)[izq + temp] = stack.pop();
		}
	}

	void mergeSort(const int &izq, const int &der) {
		if (izq < der) {
			int mit = (izq + der) / 2;
			mergeSort(izq, mit);
			mergeSort(mit + 1, der);
			ordenaMerge(izq, mit, der);
		}
	}

	void sort(void) {
		mergeSort(1, tam);
	}

	// Funcion que imprime la DLL en un archivo de salida (dll_ordenada.txt)
	void print(string archivo) {
		ofstream salida(archivo);
		Node<T> *aux = head;
		while (aux != nullptr) {
			salida << aux->data << endl;
			aux = aux->next;
		}
		salida.close();
	}
};

// Funcion que realiza la busqueda de las fechas ingresadas por el usuario
int busqBinaria(DoublyLinkedList<Info> &lista, const Fecha &valor) {
	int izq = 1, der = lista.getTam(), mid;
	while (izq <= der) {
		mid = izq + (der - izq) / 2;
		if ((Fecha) (lista[mid].fecha) == valor) {
			return mid;
		}
		if ((Fecha) (lista[mid].fecha) < valor) {
			izq = mid + 1;
		} 
		else {
			der = mid - 1;
		}
	}
	return mid;
}

// Funcion menu (se pregunta al usuario la fecha de inicio y fin y se van desplegando los datos)
void menu(DoublyLinkedList<Info> &data) {
	Fecha inicio, fin;
	string mes, hora;
	int dia;
    cout << "Fecha y hora de inicio" << endl;
	cout << "Ingresar la fecha y hora de inicio con el formato del archivo bitacora.txt (Feb 20 07:11:05)" << endl;
	cin >> mes >> dia >> hora;
	inicio = Fecha(stoi_mes(mes), dia, hora);
    cout << "Fecha y hora final" << endl;
	cout << "Ingresar la fecha y hora final con el formato del archivo bitacora.txt (Feb 20 07:11:05)" << endl;
	cin >> mes >> dia >> hora;
	fin = Fecha(stoi_mes(mes), dia, hora);

	int izq = busqBinaria(data, inicio), der = busqBinaria(data, fin);

	bool interruptor = true;
	char op;
	int contador = 1;
	for (int i = izq; i <= der; i++) {
		if(contador%11 != 0) {
			cout << data[i] << endl;
		}
		else {
			cout << "Mostrar los siguientes elementos 10 (S / N)?" << endl;
			cin >> op;
			if(op == 'S') {
				interruptor = true;
			}
			else {
				interruptor = false;
			}
		}
		contador++;
		if(interruptor == false) {
			break;
		}
	}

	char aux;
	cout << "Desea realizar otra operacion (S / N)?" << endl;
	cin >> aux;
	if (aux == 'S') {
		menu(data);
	} 
	else {
		return;
	}
}

// Funcion principal (se crea la DLL y se lee el archivo bitacora.txt y se mandan a llamar otras funciones)
int main() {
	DoublyLinkedList<Info> data;
	string mes, hora, ip, falla;
	int dia;
	ifstream archivo("bitacora.txt");
	while (archivo >> mes >> dia >> hora >> ip) {
		getline(archivo, falla);
		falla.erase(falla.begin());
		data.insert(Info(Fecha(stoi_mes(mes), dia, hora), ip, falla));
	}
	archivo.close();
	cout << "Puede tardar un tiempo en ordenar la lista..." << endl;
	data.sort();
	data.print("dll_ordenada.txt");
	menu(data);
	
	return 0;
}