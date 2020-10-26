#pragma once

#include <iostream>
#include <string>

using namespace std;

template<class T>
struct Node {
    Node(T data);
    Node(T data, Node<T> *next, Node<T> *prev);
    T data;
    Node<T> *next;
    Node<T> *prev;
};

template<class T>
Node<T>::Node(T datos) {
    data = datos;
    next = nullptr;
    prev = nullptr;
}

template<class T>
Node<T>::Node(T datos, Node<T> *next, Node<T> * prev) {
    data = datos;
    this ->next = next;
    this-> prev = prev;
}