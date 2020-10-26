#pragma once
#include "DoubleLinkedList.h"

template<class T>
class Heap{
    private:

        DoubleLinkedList<T> heap;
        int size;
        void downSort(int index);
        void swap(int a, int b);
        void insertar(DoubleLinkedList<T>, int);
    public:
    
        Heap();
        Heap(DoubleLinkedList<T> list);
        bool isEmpty();
        void print();
        T remove();
        void insert(T);
};

template<class T>
Heap<T> :: Heap(){
    size = 0;
}

// Complejida: O(1)
template<class T>
Heap<T> :: Heap(DoubleLinkedList<T> list)
{
    if(!list.isEmpty() ){
        heap = list;
        size = list.getSize();
        int index = size/2;
        downSort(index);
    }
}

// Complejida: O(1)
template<class T>
bool Heap<T> :: isEmpty()
{
    return size == 0;
}

// Complejida: O(1)
template<class T>
void Heap<T> :: swap(int a, int b)
{
    T aux = heap[a];
    heap[a] = heap[b];
    heap[b] = aux;
}

// Complejida: O(2n)
template<class T>
void Heap<T> :: downSort(int index){
    while(index >= 1){
        int pos = index;
        while(pos*2 <= size){
            int s1 = pos*2;
            int s2 = pos*2 + 1;
            int max;
            if (s2 > size){
                max = s1;
            }
            else{
                heap[s1] > heap[s2] ? max = s1 : max = s2;
            }
            if(heap[max] > heap[pos]){
                swap(pos,max);
                pos = max;
            } else{
                pos = size;
            }
        }
        index--;
    }
}

// Complejida: O(1)
template<class T>
void Heap<T> :: print(){
    heap.print();
}

// Complejida: O(1)
template<class T>
T Heap<T> :: remove(){
    if(!isEmpty()){
        T aux = heap[1];
        swap(1,size);
        heap.deleteLast();
        size--;
        downSort(1);
        return aux;
    } else{
        throw runtime_error("The heap is empty");
    }
}

// Complejida: O(n^2)
template<class T>
void Heap<T> :: insert(T data)
{
    heap.addLast(data);
    size = size + 1;
    insertar(heap,size);
}

// Complejida: O(n^2)
template<class T>
void Heap<T> :: insertar(DoubleLinkedList<T> aux,int n){

    if(n > 1){
        int padre = n/2;
        if(aux[n] > aux[padre]){
            swap(n,padre);
            insertar(aux,padre);
        }
    }
}