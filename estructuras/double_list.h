//
// Created by JLeandroJM on 30/05/23.
//

#ifndef PROYECTOAED_DOUBLE_LIST_H
#define PROYECTOAED_DOUBLE_LIST_H

#include<iostream>
template<typename T>
struct NodeD {
    T data;
    NodeD<T>* next = nullptr;
    NodeD<T>* prev = nullptr;

    NodeD() = default;

    NodeD(T value) {
        this->data = value;
    }

    void killSelf() {
        next = nullptr;
        prev = nullptr;
    }

    ~NodeD() {
        this->killSelf();
    }
};

template <typename T>
class DoubleList {


private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int nodes;

public:
    DoubleList() : head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList(){
        clear();
    }

    T front(){
        return head->data;
    }

    T back(){
        return tail->data;
    }

    void push_front(T data){
        NodeD<T>* t = new NodeD<T>(data);
        t->next = head;
        t->prev = nullptr;
        if (is_empty()) tail = t;
        else head->prev = t;
        head = t;
        nodes++;
    }

    void push_back(T data){
        NodeD<T>* t = new NodeD<T>(data);
        t->next = nullptr;
        t->prev = tail;
        if (is_empty()) head = t;
        else tail->next = t;
        tail = t;
        nodes++;
    }

    T pop_front(){
        if (is_empty()) {
            throw ("No hay elementos en la lista");
        }

        T temp = head->data;

        if (nodes == 1) {
            delete head;
            head = tail = nullptr;
        }
        else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        nodes--;
        return temp;
    }

    T pop_back(){
        if (is_empty()) {
            throw ("No hay elementos en la lista");
        }

        T temp = tail->data;

        if (nodes == 1) {
            delete tail;
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        nodes--;
        return temp;
    }

    T insert(T data, int pos){
        if (pos<0 or pos>nodes) throw ("Posicion fuera de rango");
        if (pos == 0) {
            push_front(data);
            return data;
        }
        else if (pos == nodes){
            push_back(data);
            return data;
        }
        NodeD<T>* node = new NodeD<T>(data);
        NodeD<T>* t = head;
        for (int i=1; i<pos; i++) t = t->next;
        node->next = t->next;
        node->prev = t;
        t->next->prev = node;
        t->next = node;
        nodes++;
        return data;
    }

    bool remove(int pos){
        if (pos<0 or pos>=nodes) throw ("Posicion fuera de rango");
        if (pos == 0) {
            pop_front();
            return true;
        }
        else if (pos == nodes-1) {
            pop_back();
            return true;
        }
        NodeD<T>* t = head;
        for (int i=0; i<pos; i++) t = t->next;
        t->next->prev = t->prev;
        t->prev->next = t->next;
        return true;
    }

    T& operator[](int pos){
        if (!(0 <= pos < nodes)) {
            throw ("Posicion fuera de rango");
        }
        NodeD<T>* t = head;
        for(int i=0; i<pos; i++) t = t->next;
        return t->data;
    }

    bool is_empty(){
        return nodes == 0;
    }

    int size(){
        return nodes;
    }

    void clear(){
        if (nodes == 0) return;
        else if (nodes == 1) {
            delete tail;
            tail = nullptr;
            head = nullptr;
        }
        else {
            while (tail != nullptr) {
                NodeD<T>* temp = tail->prev;
                delete tail;
                tail = temp;
            }
        }
        nodes = 0;
    }

    void sort(){
        head = mergeSort(head);
    }

    bool is_sorted(){
        if (nodes < 2) return true;
        NodeD<T>* t = head;
        while (t->next != nullptr){
            if (t->data > t->next->data) return false;
            t = t->next;
        }
        return true;
    }

    void reverse(){
        NodeD<T>* t1 = head;
        NodeD<T>* t2 = tail;
        while (t1 != t2){
            T t = t1->data;
            t1->data = t2->data;
            t2->data = t;
            if (t1->next == t2){
                break;
            }
            t1 = t1->next;
            t2 = t2->prev;
        }
    }

    std::string name(){
        return "ForwardList";
    }

};
template <typename T>
NodeD<T> *merge(NodeD<T> *first, NodeD<T> *second) {
    if (!first)
        return second;

    if (!second)
        return first;

    if (first->data < second->data)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

template <typename T>
NodeD<T> *mergeSort(NodeD<T> *head) {
    if (!head || !head->next)
        return head;
    NodeD<T> *second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head,second);
}

template<typename T>
NodeD<T> *split(NodeD<T> *head) {
    NodeD<T> *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    NodeD<T> *temp = slow->next;
    slow->next = NULL;
    return temp;
}


#endif //PROYECTOAED_DOUBLE_LIST_H
