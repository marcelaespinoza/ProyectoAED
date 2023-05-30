#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int M = 5;

template<typename TK>
struct Node
{
    TK *keys;
    Node** children;
    int count; 
    bool leaf;

    Node(): keys(nullptr), children(nullptr), count(0), leaf(true) {}

    Node(vector<TK> elements)
    {
        this->keys = new TK[M - 1];
        this->children = new Node<TK>*[M];
        this->count = 0;
        this->leaf = true;
        int i = 0;
        for (auto itr: elements) {
            keys[i] = itr;
            count++;
            i++;
        }
    }

    void link_child(int index_child, vector<TK> elements)
    {
        leaf = false;
        Node<TK>* child = new Node(elements);
        children[index_child] = child;
    }

    bool search(TK key)
    {
        int i = 0;
        while (i < count && key > keys[i]) {
            i++;
        }

        if (keys[i] == key) {
            return true;
        }

        if (leaf == true) {
            return false;
        }

        return children[i]->search(key);
    }

	vector<TK> starts_with(TK prefix) // retorna vector
{
    vector<TK> results;

    int i = 0;
    while (i < count && prefix > keys[i])
    {
        i++;
    }

    // Busca en keys quien cumple con el prefijo
    while (i < count && keys[i].find(prefix) == 0)
    {
        results.push_back(keys[i]);
        i++;
    }

    // busqueda en hijos
    if (leaf == false)
    {
        for (int j = 0; j <= count; j++)
        {
            if (children[j] != nullptr)
            {
                vector<TK> children_prefix = children[j]->starts_with(prefix);
                results.insert(results.end(), children_prefix.begin(), children_prefix.end()); // se agrega elementos del vector
            }
        }
    }

    return results;
}



    string toString(string sep)
    {
        string result = "";
        int i;
        for(i = 0; i < count; i++)
        {
            if(children[i] != nullptr)
                result += children[i]->toString(sep);
            result += keys[i] + sep;
        }
        if(children[i] != nullptr)
            result += children[i]->toString(sep);
        return result;
    }
};
