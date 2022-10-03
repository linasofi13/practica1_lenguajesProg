#include <iostream>
#include <string>
#include "Nodo.h"
#include "Lista.h"
using namespace std;

void Lista::push(Nodo* data){
    data->next = this->head;
    this->head = data;
}

Nodo* Lista::pop(){
    Nodo* tmp = this->head;
    this->head = this->head->next;
    return tmp;
}

