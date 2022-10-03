#include <iostream>
#include <string>
#include "Nodo.h"
#include "Lista.h"
#include "Verificador.h"
using namespace std;

// ** Definicion de Metodos para Chequear la Expresion **
Verificador::Verificador() {}

bool Verificador::isInteger(const string& s) // chequea si el caracter ingresado es un int
{
    return !s.empty() && find_if(s.begin(),
                                 s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}
bool Verificador::isFloat(string myString) { // chequea si el caracter ingresado es un float
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // considera el espacio en blanco invalido
    // chequea el string y si es failbit o badbit
    return iss.eof() && !iss.fail();
}
int Verificador::contadorOperadores(string eq, int longitudEq){ // cantidad de operadores en la expresion
    int contador = 0;
    for (int i = 0; i < longitudEq; i++) {
        char caracter = eq[i+1];
        string letra(1, caracter);
        if ((eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/') and (isFloat(letra) == false or isInteger((letra)) == false)){
            contador = contador + 1;
        }
    }
    return contador;
}
int Verificador::contadorNumeros(string eq, int longitudEq){ // cantidad de numeros en la expresion
    int contadorTotal = 0;
    int contadorInts = 0;
    int contadorFloats = 0;
    if(longitudEq == 1 or longitudEq == 2){
        return 1;
    } else {
        stringstream ss;
        ss << eq;
        vector <int> vectorNumerosInt;
        vector <float> vectorNumerosFloat;
        string temp;
        int num;
        float num2;
        while(!ss.eof()){
            ss >> temp;
            if (stringstream(temp) >> num){
                vectorNumerosInt.push_back(num);

            } else if (stringstream(temp) >> num2){
                vectorNumerosFloat.push_back(num2);
            }
        }
        for (int i=0; i<vectorNumerosInt.size(); i++){
            contadorInts = contadorInts + 1;
        }
        for (int i=0; i<vectorNumerosFloat.size(); i++){
            contadorFloats = contadorFloats + 1;
        }
        contadorTotal = contadorInts + contadorFloats;
    }
    return contadorTotal;
}

bool Verificador::chequearQueSoloHayanNumerosYOperadores(string eq){ // chequea que el usuario no ingrese caracteres no permitidos
    for (int i = 0; i < eq.length(); i++) {
        char caracter = eq[i];
        string letra(1, caracter);
        if ((eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/' || isFloat(letra) == true || isInteger((letra)) == true || eq[i] == ' ')){
            return true; // solo hay numeros y operadores
        }else {
            return false; // hay algo raro
        }
    }
}
bool Verificador::chequearCantidadDeEspaciosEnBlanco(string eq){ // chequea que el usuario no ingrese mas espacios de los necesarios
    int cantidadNumeros = contadorNumeros(eq, eq.length());
    int cantidadOperadores = contadorOperadores(eq, eq.length());
    int sumaNumOperadores = cantidadNumeros + cantidadOperadores;
    int cantidadEspacios = 0;
    for (int i = 0; i < eq.length(); i++) {
        if(eq[i] == ' '){
            cantidadEspacios = cantidadEspacios + 1;
        }
    }
    if (cantidadEspacios == sumaNumOperadores-1){
        return true; // la cantidad de espacios esta bien
    } else {
        return false; // hay mas espacios de los que deberia
    }

}
bool Verificador::chequearSiHayUnOperadorAlInicio(string eq) { // chequea que el usuario no ingrese un operador al inicio (deben ir despues de los numeros)
    char caracter0 = eq[0];
    char caracter = eq[1];
    string letra(1, caracter); // letra es en la posicion 1
    string letra0(1, caracter0);
    //cout << s << std::endl;
    if ((eq[0] == '+' or eq[0] == '-' or eq[0] == '*' or eq[0] == '/') and
        (isFloat(letra) == true or isInteger((letra)) == true)) {
        return false; // hay un operador al inicio pero es el signo de un numero
    } else if ((eq[0] == '+' or eq[0] == '-' or eq[0] == '*' or eq[0] == '/') and (eq[1] == ' ')) {
        return true; // hay un error
    } else if (isFloat(letra0) == true or isInteger((letra0)) == true) { // si hay un numerito solo
        return false; // por defecto
    }
}

void Verificador::notacionPolaca(vector<string> v, Lista *pila) { // realiza el calculo de la expresion
    for (size_t i = 0; i < v.size(); i++) {
        //cout << v[i];
        if (isFloat(v[i]) or isInteger(v[i])) {
            //  cout << v[i] << endl;
            float num = stof(v[i]);
            pila->push(new Nodo(num, NULL));
        } else {
            Nodo *pop1 = pila->pop();
            Nodo *pop2 = pila->pop();
            //cout << pop1->getNumero() << endl;
            //cout << pop2->getNumero() << endl;

            if (v[i] == "+") {
                float suma = pop1->getNumero() + pop2->getNumero();
                //cout << suma;
                pila->push((new Nodo(suma, NULL)));

            } else if (v[i] == "-") {
                float resta = pop2->getNumero() - pop1->getNumero();
                // cout << resta;
                pila->push((new Nodo(resta, NULL)));

            } else if (v[i] == "*") {
                float multiplicacion = pop2->getNumero() * pop1->getNumero();
                // cout << multiplicacion;
                pila->push((new Nodo(multiplicacion, NULL)));

            } else if (v[i] == "/") {
                float division = pop2->getNumero() / pop1->getNumero();
                string valor = (to_string(division)).substr(0, 4); // para obtener menos decimales
                float valor2  = stod(valor);
                pila->push((new Nodo(valor2, NULL)));

            }
        }
    }
    cout << pila->pop()->getNumero() << endl; // imprime el resultado
}
void Verificador::calcular(Lista *pila) { // metodo que lleva al ciclo infinito de ingresar una expresion (aqui chequea la expresion en general)
    bool condicion2 = true;
    while (condicion2) {
        cout << "--- | Ingresa una expresion: " << endl;
        string eq;
        getline(cin, eq);
        if (eq != " " and eq.find(' ') != string::npos and
            contadorOperadores(eq, eq.length()) < contadorNumeros(eq, eq.length()) and chequearCantidadDeEspaciosEnBlanco(eq) == true and
            chequearSiHayUnOperadorAlInicio(eq) == false and chequearQueSoloHayanNumerosYOperadores(eq) == true)  {

            vector<string> v; // vector que almacena la expresion

            stringstream ss(eq);

            while (ss.good()) {
                string substr;
                getline(ss, substr, ' ');
                v.push_back(substr);
            }
            /*for (int i = 0; i < v.size(); i++) {
                cout << v[i] << endl; // para imprimir el vector
             }*/
            if (eq.length() == 0) {
                cout << "Usted ha brindado una cadena vacia";
            } else {
                try {
                    cout << "----- | El resultado es: | ----- " << endl;
                    notacionPolaca(v, pila); // salta al calculo de la expresion, luego de haberla verificado
                    cout << "----------------------------------" << endl;
                }
                catch (...) {
                    cout << "Usted ha ingresado una expresion invalida." << endl;
                    cout << "Por favor verifique que no haya agregado caracteres invalidos y vuelva a intentarlo"
                         << endl;
                }
            }
            condicion2 = false; // nos saca del ciclo infinito para volver al menu principal
        } else { // este bloque de instrucciones aparecera cada que el usuario no cumpla con alguna de las condiciones
            cout << "*** Recuerde ***" << endl;
            cout << " | No ingrese un espacio en blanco al inicio de la expresion" << endl;
            cout << " | Por favor ingrese cada valor separado por un espacio en blanco, no juntos." << endl;
            cout << " | No ingrese mas operadores que numeros" << endl;
            cout << " | No ingrese un operador al inicio de la expresion" << endl;
            cout << " | No ingrese caracteres no relacionados con la expresion polaca" << endl;
        } // estas instrucciones son notificadas para que el usuario corrija la expresion
    } // el bloque "else" es el resultado de que alguna de las condiciones de verificacion de la expresion no se cumpla
}
