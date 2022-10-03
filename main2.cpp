#include <iostream>
#include <vector>
#include "Lista.h"
#include "Verificador.h"
using namespace std;

int main() { // * main *
    Lista *pila = new Lista(); // crear stack
    Verificador* expresion = new Verificador();
    bool condicion = true;
    while (condicion) { // ciclo infinito del menu principal
        cout << "----| Calculadora de Expresiones de Notacion Posfija | ------" << endl;
        cout << "- - - - - | Bienvenido | - - - - - " << endl;
        cout << "| * | Esta calculadora calcula expresiones en Notacion Polaca Posfija | * |" << endl;
        cout << "| * | Unicamente realiza operaciones de suma, resta, multiplicacion y division (+, -, *, /)  | * |"
             << endl;
        cout
                << "| * | Se realizan operaciones tanto para enteros positivos/negativos como para decimales positivos/negativos | * |"
                << endl;
        cout << "| * | Siga las instrucciones a la hora de ingresar una expresion | * |" << endl;
        cout << "--- | Pulse 1 para ingresar una expresion | ---    " << endl;
        cout << "--- | Pulse 2 para salir | ---   " << endl;
        cout << "";
        int opcion;
        if (cin >> opcion) {
            switch (opcion) {
                case 2:
                    cout << "Hasta luego !" << endl;
                    condicion = false;
                    break;
                case 1:
                    expresion->calcular(pila);
                    break;
                default:
                    cout << "--------------------------" << endl;
                    cout << "--- Opcion Incorrecta ---" << endl;
                    cout << "--------------------------" << endl;
            }
        } else {
            cout << "--------------------------" << endl;
            cout << "--- Opcion Incorrecta ---" << endl;
            cout << "--------------------------" << endl;
            cin.clear();
            cin.ignore( 1000, '\n') ;
        }
    } return 0;
}

// *** Explicacion Metodos de Verificacion de la expresion ** --> se encuentran en la clase "Verificador.h"
/*cout << contadorOperadores(eq, eq.length()) << endl;// --> para ver que no hayan mas operadores que numeros
        cout << contadorNumeros(eq, eq.length()) << endl; //--> retorna int, cantidad de numeros en la expresion
        cout << chequearSiHayUnOperadorAlInicio(eq) << endl;// --> chequea que el usuario no haya ingresado un operador al inicio (notacion erronea)
        cout << chequearCantidadDeEspaciosEnBlanco << endl; //-->  retorna true si los espacios entre caracteres estan bien
        cout << (eq.find(' ') != string::npos) << endl; // --> verifica que el usuario no nos haya mandado el texto junto
        cout << chequearQueSoloHayanNumerosYOperadores(eq) << endl; // --> chequea que no hayan caracteres extraños
        cout << (eq != " ") << endl; // --> para chequear que no nos haya entregado una cadena vacia
        eq.find(' ') != string::npos //--> para chequear si el usuario nos dio los numeros separados
       eq != " " //--> para chequear que no nos haya dado un espacio como input*/
// estos metodos se pueden incluir dentro de la funcion "calcular" para ver los resultados que arroja cada uno.
