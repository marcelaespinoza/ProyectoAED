#pragma  once

#ifndef PROYECTO_NODES_H
#define PROYECTO_NODES_H

#endif //PROYECTO_NODES_H

#include <iostream>
#include <functional>

namespace nodo_l{
    template <class t>
    struct node{
        t data;
        node<t> * prev;
        node<t>* next;
        node()=default;
        ~node()=default;
        explicit node(t data, node<t>*next, node<t>* prev);

    };
    template<class t>
    node

}