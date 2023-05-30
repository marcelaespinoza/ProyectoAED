#include <iostream>
#include <vector>
#include <string>
#include "B+.h"
using namespace std;

void test_starts_with(){
	
    vector<string> elements;

    elements = {"alex", "balto", "carmen", "daniel"};
    Node<string>* root = new Node<string>(elements);
    elements = {"alonso", "arnold"};
    root->link_child(0, elements);
    elements = {"blaziken", "carol"};
    root->link_child(1, elements);
    elements = {"dereck", "ernesto"};
    root->link_child(2, elements);
    elements = {"grace", "karla", "leandro", "marcela"};
    root->link_child(3, elements);
    elements = {"ortencia", "pamela", "perez", "perezoso"};
    root->link_child(4, elements);
		string prefix = "";
		cout<<"Ingrese prefijo: "<< endl;
		cin >> prefix;
		vector<string> words = root->starts_with(prefix);
		cout << "Inicia con: " << prefix << endl;
		for (const string& word : words){
    		cout << word << endl;
		}
	}
int main()
{
    test_starts_with();
    return 0;
}
