#include <iostream>
#include <string>

using namespace std;

struct Tarea {
    string titulo;
    string descripcion;
    bool completada;
    struct Tarea* siguiente;    
};

struct Lista {
    int longitud;
    struct Tarea* cabeza;
};

Tarea* crearNodo() {
    Tarea* nuevo = new Tarea;
    cout << "Ingrese el titulo de la tarea: ";
    fflush(stdin);
    getline(cin, nuevo->titulo);
    cout << "Ingrese la descripcion de la tarea: ";
    fflush(stdin);
    getline(cin, nuevo->descripcion);
    nuevo->completada = false;
    nuevo->siguiente = nullptr;

    return nuevo;
}

void enlazarNodoBack(Lista*& lista) {
    if (lista == nullptr) {
        lista = new Lista;
        lista->longitud = 1;
        lista->cabeza = crearNodo();
    } else if (lista->cabeza == nullptr) {
        lista->longitud = 1;
        lista->cabeza = crearNodo();
    } else {
        Tarea *aux = lista->cabeza;
        while (aux->siguiente != nullptr) {
            aux = aux->siguiente;
        }
        aux->siguiente = crearNodo();
        lista->longitud++;
    }
}
void enlazarNodoFront(Lista*& lista) {
    if (lista == nullptr) {
        lista = new Lista;
        lista->longitud = 1;
        lista->cabeza = crearNodo();
    } else {
        if (lista->cabeza == nullptr) {
            lista->cabeza = crearNodo();
            lista->longitud++;
        } else {
            Tarea *aux = lista->cabeza;
            lista->cabeza = crearNodo();
            lista->cabeza->siguiente = aux;
            lista->longitud++;
        }
    }
}

void mostrarLista(Lista *&lista) {
    if (lista == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    Tarea *aux = lista->cabeza;
    while (aux != nullptr) {
        cout << "Titulo: " << aux->titulo << "\n";
        cout << "Descripcion: " << aux->descripcion << "\n";
        if (aux->completada) {
            cout << "La tarea esta completada.\n";
        } else {
            cout << "La tarea no esta completada.\n";
        }
        aux = aux->siguiente;
    }
}