/** 
Programa que combina hace un merge de dos listas doblemente ligadas en una sola 
lista doblemente ligada, cada lista tendra n nodos con valores aleatorios 

*/

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor)
        : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};
            
Lista* crearLista() {
    Lista* lista = new Lista();
    int n;
    cout << "Ingrese el numero de nodos: ";
    cin >> n;
   
    return lista;
}