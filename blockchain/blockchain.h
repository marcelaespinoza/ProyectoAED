#pragma once


#ifndef PROYECTOAED_BLOCKCHAIN_H
#define PROYECTOAED_BLOCKCHAIN_H
#include "block.h"
#include <fstream>
#include <string>
#include <sstream>
#include <forward_list>

class Blockchain {
private:
    std::forward_list<block*>chain{};
    Hash<std::string, node_l::node<block*>*>  userhash{};//el constructor de btree tiene que tener (tamaño,function,function,function,function)
    btree<transaction*>ordenPorFecha{
        30,
        [](const transaction *first,const transaction * second){return  first->date < second->date;},
        [](const transaction *first,const transaction *second){return  first->date > secod->date;},
        [](const transaction *first, const transaction *second){return first->date=second->date;},
    };

    btree<transaction*>ordenporCantidadDinero{ //el constructor de btree tiene que tener (tamaño,function,function,function,function)
        30,
        [](const transaction *first, const transaction *second ){return first->montoCantida < second->montoCantidad;},
        [](const transaction *first, const transaction *second ){return first->montoCantida > second->montoCantidad;},
        [](const transaction *first, const transaction *second ){return first->montoCantida = second->montoCantidad;},
    public:
        //constructores
        Blockchian()=def
    };

};



#endif //PROYECTOAED_BLOCKCHAIN_H
