//
// Created by JLeandroJM on 30/05/23.
//

#ifndef PROYECTOAED_HEAP_H
#define PROYECTOAED_HEAP_H

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Heap
{
public:
    enum Type {
        MAX_HEAP, MIN_HEAP
    };

private:
    T *elements;
    int capacity;
    int n;
    Type type;

public:
    Heap(T *elements, int n, Type type=MAX_HEAP) : elements(elements), n(n), type(type){
        for(int i = n-1; i >= 0 ; i--){
            heapify_up(i);
        }
    }


    Heap(int capacity, Type type=MAX_HEAP) : capacity(capacity), type(type)
    {
        elements = new T[capacity];
        n = 0;
    }

    ~Heap(){
        delete [] this-> elements;
    }


    void heapify(int n, int i) {
        if(type==MIN_HEAP){
            int smallest = i;
            int left = Left(i);

            int right = Right(i);
            if (left < n && this->elements[left] < this->elements[smallest]) {
                smallest = left;
            }
            if (right < n && this->elements[right] < this->elements[smallest]) {
                smallest = right;
            }
            if (smallest != i) {
                std::swap(this->elements[i], this->elements[smallest]);
                heapify(n, smallest);
            }

        }
        else if(type==MAX_HEAP){

            int largest = i;
            int left = Left(i);
            int right = Right(i);
            if (left < n && this->elements[left] > this->elements[largest]) {
                largest = left;
            }
            if (right < n && this->elements[right] > this->elements[largest]) {
                largest = right;
            }
            if (largest != i) {
                std::swap(this->elements[i], this->elements[largest]);
                heapify(n, largest);
            }

        }
        else{return;}

    }


    void buildFromArray(T *elements, int n){
        for(int i = 0; i < n ; i++){
            push(elements[i]);
        }
    }

    int size(){return n;}

    bool is_empty(){
        if(n == 0) return true;
        else return false;
    }

    void push(T value){
        if(n == capacity){//Redimensionar
            capacity = capacity *2;
            T *nuevo = new T[capacity];
            for(int i = 0; i < capacity/2 ; i++){
                nuevo[i] = elements[i];
            }
            delete[] elements;
            elements = nuevo;
        }
        elements[n] = value;
        heapify_up(n-1);
        n = n + 1;
    }

    T pop(){
        if(n == 0){return NULL;}
        T temp = elements[0];
        swap(elements[0], elements[n-1]);
        n = n - 1;
        heapify_down(0);
        return temp;
    }

    T top(){


        return this->elements[0];
    }

    vector<T> extractTheTopK(int k) {
        vector<T> result;
        for (int i = 0; i < k; i++) {
            if (is_empty()) {
                break;
            }
            result.push_back(pop());
        }
        return result;
    }

    static void sortAsc(T* arr, int n){
        Heap<T>* temp = new Heap<T>(arr,n, Heap<int>::MAX_HEAP);
        for(int i = 0; i<n; i++){
            temp->pop();
        }
    }

    static void sortDesc(T* arr, int n){
        Heap<T>* temp = new Heap<T>(arr,n, Heap<int>::MIN_HEAP);
        for(int i = 0; i < n; i++){
            temp->pop();
        }

    }





private:
    int Parent(int i){return (i - 1) / 2;}

    int Left(int i){return (2 * i + 1);}

    int Right(int i){return (2 * i + 2);}

    void heapify_down(int i){
        if (i<0) return;
        else if(type == MAX_HEAP){
            int left_child = Left(i);
            int right_child = Right(i);
            int largest = i;

            if (left_child < this->size() && elements[left_child] > elements[largest]) largest = left_child;
            if (right_child < this->size() && elements[right_child] > elements[largest]) largest = right_child;
            if (largest != i) {
                swap(elements[i], elements[largest]);
                heapify_down(largest);
            }
        }else if( type == MIN_HEAP){
            int left_child = Left(i);
            int right_child = Right(i);
            int smallest = i;
            if (left_child < this->size() && elements[left_child] < elements[smallest]) smallest = left_child;
            if (right_child < this->size() && elements[right_child] < elements[smallest]) smallest = right_child;
            if (smallest != i) {
                swap(elements[i], elements[smallest]);
                heapify_down(smallest);
            }
        }else return;

    }

    void heapify_up(int i)
    {
        if (i<=0) return;
        else if(type == MAX_HEAP){
            int parent = Parent(i);
            if (elements[i] > elements[parent]) {
                swap(elements[i], elements[parent]);
                heapify_up(parent);
            }
        }else if( type == MIN_HEAP){
            int parent = Parent(i);
            if (elements[i] < elements[parent]) {
                swap(elements[i], elements[parent]); // Intercambiamos los elementos
                heapify_up(parent); // Continuamos el heapify hacia arriba recursivamente
            }
        }else return;
    }
};


#endif //PROYECTOAED_HEAP_H
