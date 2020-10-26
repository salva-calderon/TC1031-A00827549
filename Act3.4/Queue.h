#pragma once

#include "Node.h"

template<class T>
class Queue {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
        
    public:
        Queue();
        T dequeue();
        T front();
        T back();
        int getSize();
        void enqueue(T data);
        void clear();
        void print();
};

template<class T>
Queue<T> :: Queue() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}


template<class T>
T Queue<T> :: dequeue() {
    if (size == 0) {
        throw runtime_error("La cola esta vacia");
    } else {
        T data = head->data;
        Node<T> *aux = head;
        head = aux->next;
        delete aux;
        size--;
        if (size == 0) {
            tail = nullptr;
        }
        return data;
    }
}

template<class T>
T Queue<T> :: front() {
    T temp;
    if (size == 0) {
        throw runtime_error("La cola esta vacia");
    } else {
        return head->data;
    }
}

template<class T>
void Queue<T> :: enqueue(T data) {
    if (size!= 0) {
        tail->next = new Node<T>(data);
        tail = tail->next;
    } else {
        head = new Node<T>(data);
        tail = head;
    }
    size++;
}

template<class T>
T Queue<T> :: back() {
    if (size == 0) {
        throw runtime_error("La cola esta vacia");
    } else {
        return tail->data;
    }
}

template<class T>
int Queue<T> :: getSize() {
    return size;
}

template<class T>
void Queue<T> :: clear() {
    int i = 1;
    while (i<= size) {
        Node<T>* aux = head;
        head = aux->next;
        delete aux;
        i++;
    }
    size = 0;
}

template<class T>
void Queue<T> :: print() {
    Node<T>* aux = head;
    for (int i = 0; i < size; i++) {
        cout << aux->data << " ";
        aux = aux->next;
    }
    cout << endl;
}