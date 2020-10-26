#pragma once

#include "Node.h"
#include "Queue.h"

template<class T>
class DoubleLinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

    public:
        DoubleLinkedList();
        void addFirst(T data);
        void addLast(T data);
        void print();
        bool isEmpty();
        void updateAt(T data, int index);
        void deleteLast();
        void clear();
        void merge(int inicio,int medio, int fin);
        void mergeSort(int inicio, int fin);
        void sort();
        void operator=(DoubleLinkedList<T> list);
        void operator=(initializer_list<T> list);
        T getData(int index);
        T& operator[](int index);
        int getSize();
};

template<class T>
DoubleLinkedList<T> :: DoubleLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
void DoubleLinkedList<T> :: operator=(initializer_list<T> list){
    if(isEmpty()) {
        for(T i : list) {
            addLast(i);
        }
    } else {
        throw runtime_error("Error, Linked list no esta vacia");
    }
}

template<class T>
void DoubleLinkedList<T> :: deleteLast() {
    Node<T>* aux = tail->prev;
    delete tail;
    tail = aux;
    size--;
}

template<class T>
void DoubleLinkedList<T> :: addFirst(T data) {
    Node<T> *nodo = new Node<T>(data);
    if (size == 0) {
        head = nodo;
        tail = nodo;
    } else {
        nodo->next = head;
        head->prev = nodo;
        head = nodo;
    }
    size++;
}

template<class T>
void DoubleLinkedList<T> :: addLast(T data) {
    Node<T> *nodo = new Node<T>(data);
    if (size == 0) {
        head = nodo;
        tail = nodo;
    } else {
        tail->next = nodo;
        nodo->prev = tail;
        tail = nodo;
    }
    size++;
}

template<class T>
int DoubleLinkedList<T> :: getSize() {
    return size;
}

template<class T>
bool DoubleLinkedList<T> :: isEmpty() {
    return size == 0;
}

template<class T>
void DoubleLinkedList<T> :: print() {
    Node<T>* aux = head;
    for (int i = 0; i < size; i++) {
        cout << aux->data.print() << endl;
        aux = aux->next;
    }
    cout << endl;
}

template <class T>
void DoubleLinkedList<T> :: updateAt(T nuevoDato, int index) {
    if(index >= 1 && index <= size) {
        if(index < size/2) {
            Node<T>* aux = head;
            int i = 1;
            while(aux != nullptr) {
                if(i == index) {
                    aux ->data = nuevoDato;
                    return;
                }
                aux = aux->next;
                i++;
            }
        }
        else {
            Node<T>* aux = tail;
            int i = size;
            while (aux != nullptr) {
                if (i == index) {
                    aux->data = nuevoDato;
                    return;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Position invalid");
}

template<class T>
T DoubleLinkedList<T> :: getData(int index) {
    if(index >= 1 && index <= size) {
        if(index < size/2) {
            Node<T>* aux = head;
            int i = 1;
            while(aux != nullptr) {
                if(i == index) {
                    return aux->data;
                }
                aux = aux->next;
                i++;
            }
        }
        else {
            Node<T>* aux = tail;
            int i = size;
            while(aux != nullptr) {
                if(i == index) {
                    return aux->data;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Position invalid");
}

template<class T>
T& DoubleLinkedList<T> :: operator[](int index) {
    if(index >= 1 && index <= size) {
        if(index < size/2) {
            Node<T>* aux = head;
            int i = 1;
            while(aux != nullptr) {
                if(i == index) {
                    return aux->data;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size;
            while(aux != nullptr) {
                if(i == index) {
                    return aux->data;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Posicion invalida");
}

template<class T>
void DoubleLinkedList<T> :: clear() {
    int i = 1;
    while(i <= size) {
        Node<T>* aux = head;
        head = aux->next;
        delete aux;
        i++;
    }
    size = 0;
}

template<class T>
void DoubleLinkedList<T>::sort() {
    mergeSort(1,size);
}

template <class T>
void DoubleLinkedList<T> :: mergeSort(int inicio, int fin)
{
    if (inicio < fin) {
        int medio = (inicio + fin)/2;
        mergeSort(inicio, medio);
        mergeSort(medio+1, fin);
        merge(inicio,medio,fin);
    }
}

template <class T>
void DoubleLinkedList<T> :: merge(int inicio, int medio, int fin) {
    int i, j, k; 
    int n1 = medio - inicio + 1; 
    int n2 = fin - medio; 

    Queue<T> L, R;

    for (i = 0; i < n1; i++) {
        L.enqueue(getData(inicio + i));
    }
         
    for (j = 0; j < n2; j++){
        R.enqueue(getData(medio + 1 + j));
    }
        
    i = 0;
    j = 0; 
    k = inicio; 
    while(i < n1 && j < n2) { 
        if(L.front() <= R.front()) { 
            updateAt(L.dequeue(),k);
            i++; 
        } 
        else{ 
            updateAt(R.dequeue(),k); 
            j++; 
        } 
        k++; 
    } 

    while(i < n1) { 
        updateAt(L.dequeue(),k);
        i++; 
        k++; 
    } 

    while(j < n2) { 
        updateAt(R.dequeue(),k);
        j++; 
        k++; 
    } 
}

template<class T>
void DoubleLinkedList<T> :: operator=(DoubleLinkedList<T> lista) {
    clear();
    for (int i = 1; i <= lista.getSize(); i++) {
        addLast(lista.getData(i));
    }
}