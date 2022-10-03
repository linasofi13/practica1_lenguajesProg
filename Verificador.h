#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include "Nodo.h"
#include "Lista.h"
using namespace std;

class Verificador{
private:

public:
    Verificador();
    bool isInteger(const string& s);
    bool isFloat(string myString);
    int contadorOperadores(string eq, int longitudEq);
    int contadorNumeros(string eq, int longitudEq);
    bool chequearQueSoloHayanNumerosYOperadores(string eq);
    bool chequearCantidadDeEspaciosEnBlanco(string eq);
    bool chequearSiHayUnOperadorAlInicio(string eq);
    void notacionPolaca(vector<string> v, Lista *pila);
    void calcular(Lista *pila);
};

