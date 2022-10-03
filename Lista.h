#pragma once
#include <iostream>
#include <string>
#include "Nodo.h"
using namespace std;

class Lista {
protected:
    Nodo* head;
public:
    Lista() {
        this->head = NULL;
    }
    void push(Nodo* data);  //comportamiento de pila
    Nodo* pop();
};
