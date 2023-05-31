#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"


using namespace std;


template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){
        data = T();
        next = nullptr;
        prev = nullptr;
    }

    Node(T value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }

    void killSelf(){
        delete this;
    }

    ~Node(){
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class ForwardList : public List<T> {


protected:
        Node<T>* head;
        int nodes;

        Node<T>* get_tail(){ // O(n)
        auto tail = head;
        while(tail->next){
            tail = tail->next;
        }
        return tail;
    }

    Node<T>* prev(Node<T>* node){
        auto current = head;
        while(current->next != node){
            current = current->next;
        }
        return current;
    }

    Node<T>* get_node(int pos){
        auto node = head;
        while(pos--){
            node = node->next;
        }
        return node;
    }

    Node<T>* get_middle(Node<T>* start){
        auto slow = start;
        auto fast = start->next;
        while (fast and fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node<T>* merge(Node<T>* left, Node<T>* right){

        auto dummyHead = new Node<T>();
        auto current = dummyHead;

        while(left and right){
            if (left->data <= right->data){
                current->next = left;
                left = left->next;
                current = current-> next;
            } else {
                current->next = right;
                right = right->next;
                current = current->next;
            }
        }

        while (left){
            current->next = left;
            left = left->next;
            current = current->next;
        }

        while (right){
            current->next = right;
            right = right->next;
            current = current->next;
        }

        return dummyHead->next;
    }

    Node<T>* merge_sort(Node<T>* start){
        if(!start->next) return start;

        auto middle = get_middle(start);
        auto start_right = middle->next;

        middle->next = nullptr; // breaking the linked list into two parts

        auto left = merge_sort(start);
        auto right = merge_sort(start_right);

        return merge(left, right);
    }




public:
        ForwardList() : List<T>() {}

        ~ForwardList(){ 
         	// TODO
             clear();
             delete head;
        }

        T front(){
           if(is_empty()) throw std::runtime_error("Forward list is empty");
           T front = head->data;
           auto temporal = head;
           head = head->next;
            delete temporal;
           --nodes;
           return front;
        }

        T back(){
            if(is_empty()) throw std::runtime_error("lista vacia");
            auto tail = get_tail();
            return tail->data;
        }

        void push_front(T data){
            auto node = new  Node<T>(data);
            node->next =this-> head;
            this->head = node;
            nodes=nodes+1;
        }

        void push_back(T data){
            if(is_empty()) push_front(data);
            else {
                auto node = new Node<T>(data);
                auto tail = get_tail();
                tail->next = node;
                nodes=nodes+1;
            }
        }

        T pop_front(){
            if(is_empty()) throw std::runtime_error("lista vacia");
            T delante = head->data;
            auto temporal = head;
            head = head->next;
            delete temporal;
            nodes=nodes-1;
            return delante;
        }

        T pop_back(){
            if(is_empty()) throw std::runtime_error("vacio");

            if(nodes == 1) return pop_front();
            else {
                auto tail = get_tail();
                auto new_tail = prev(tail);
                T back = tail->data;
                delete tail;
                new_tail->next = nullptr;
                nodes=nodes-1;
                return back;
            }
        }

        T insert(T data, int pos){
            if((pos < 0) || (nodes <= pos)){
                throw std::runtime_error("rango not");
            };

            auto nodes = new Node<T>(data);
            auto prev_node = get_node(pos - 1);
            auto next_node = get_node(pos);

            prev_node->next = nodes;
            nodes->next = next_node;
            nodes++;

            return data;
        }

        bool remove(int pos){
            if((pos < 0) || (this->nodes <= pos)){
                throw std::runtime_error("Forward list index out of range");

            };

            if(pos == 0){ pop_front();}
            else if(pos == nodes - 1) pop_back();
            else {
                auto node = get_node(pos);
                auto prev_node = get_node(pos - 1);
                auto next_node = get_node(pos + 1);
                prev_node->next = next_node;
                delete node;
                nodes=nodes-1;
            }
            return true;        }

        T& operator[](int pos){
            if((pos < 0) || (nodes <= pos)){
                throw std::runtime_error("range index not");
            }
            auto node = get_node(pos);
            return node->data;        }

        bool is_empty(){
            return !nodes;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while(nodes >= 1){
                this->pop_front();
            }
            head = nullptr;
        }
        
        void sort(){
            this->head= merge_sort(head);
        }

        bool is_sorted(){
            if(nodes <= 1) return true;

            auto current = head;
            while(current->next){
                if(current->data > current->next->data){
                    return false;
                }
                current = current->next;
            }
            return true;
        }

        void reverse(){
            if(this->nodes <= 1) return;
            // It's all about updating tha link part of the nodes and head pointer
            auto current = this->head;
            Node<T>* next = nullptr;
            Node<T>* prev = nullptr;

            while(current){
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            this->head = prev;
        }

        string name(){
            return "ForwardList";
        }

        
};

