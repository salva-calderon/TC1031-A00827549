// Nombre: Guillermo Salvador Calderon Lopez
// Matricula: A00827549

#ifndef Heap_h
#define Heap_h

template<class T>
class Heap {
    private:
        std::vector<T> heap;
        int size;
        void downSort(int index);
        void swap(int a, int b);
        void upSort();
        
    public:
        Heap();
        Heap(std::vector<T> list);
        T remove();
        void insert(T data);
        bool isEmpty();
        void print();
        std::vector<T> sort();
};

// O(1)
template<class T>
Heap<T>::Heap() {
    size = 0;
}

// O(1)
template<class T>
void Heap<T>::swap(int a, int b) {
    T aux = heap[a];
    heap[a] = heap[b];
    heap[b] = aux;
}

// O(log n)
template<class T>
void Heap<T>::downSort(int index) {
    while (index >= 1) {
        int pos = index;
        while (pos*2<=size) {
            int s1 = pos * 2;
            int s2 = pos * 2 + 1;
            int max;
            if (s2 > size) {
                max = s1;
            } else {
                heap[s1].times > heap[s2].times ? max = s1 : max = s2;
            }
            if (heap[max].times > heap[pos].times) {
                swap(pos,max);
                pos = max;
            } else {
                pos = size;
            }
        }
        index--;
    }
}

// O(log n)
template<class T>
T Heap<T>::remove() {
    if (!isEmpty()) {
        T aux = heap[1];
        swap(1,size);
        heap.pop_back();
        size--;
        downSort(1);
        return aux;
    }
    else {
        throw std::runtime_error("Heap esta vacia");
    }
}

// O(log n)
template<class T>
void Heap<T>::upSort() {
    int pos = size;
    while (pos > 1) {
        int father = pos / 2;
        if (heap[pos] > heap[father]) {
            swap(father, pos);
            pos = father;
        } else {
            pos = 1;
        }
    }
}

// O(log n)
template<class T>
void Heap<T>::insert(T data) {
    heap.addLast(data);
    size++;
    upSort();
}

// O(n)
template<class T>
Heap<T>::Heap(std::vector<T> list) {
    if (list.size()>1) {
        heap = list;
        size = heap.size()-1;
        int index = size / 2;
        downSort(index);
    } else {
        size = 0;
    }
}

// O(n)
template<class T>
void Heap<T>::print() {
    heap.print();
}

// O(nlogn)
template <class T>
std::vector<T> Heap<T>::sort() {
    std::vector<T> aux;
    while(size>0) {
        aux.push_back(remove());
    }
    return aux;
}

// O(1)
template<class T>
bool Heap<T>::isEmpty() {
    return size == 0;
}

#endif