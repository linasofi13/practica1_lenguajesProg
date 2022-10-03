#pragma once
#include <iostream>
#include <string>
using namespace std;

class Nodo {
    protected:
    float data;
    public:
        Nodo* next;
        Nodo(float data, Nodo* next);
        Nodo();
        float getNumero();
};

