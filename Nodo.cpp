#include <iostream>
#include "Nodo.h"
using namespace std;

Nodo::Nodo(float data, Nodo* next){
    this->data = data;
    this->next = next;
}
Nodo::Nodo(){
    this->data = 0;
}
float Nodo::getNumero(){
    return this->data;
}
