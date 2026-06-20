#include <iostream>
using namespace std;

// Estructura del nodo
struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int valor):
        dato(valor), siguiente(nullptr) {}
};

Nodo* NuevoNodo(int valor) {
    Nodo* nodo = new Nodo(valor);
    return nodo;
}

void PushBack(Nodo* &cabeza, int valor) {
    Nodo* nuevo = NuevoNodo(valor);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != cabeza) temp = temp->siguiente;
        temp->siguiente = nuevo;
        nuevo->siguiente = cabeza;
    }
}

void print(Nodo* cabeza) {
    if (cabeza == nullptr) return;
    Nodo* temp = cabeza;
    do {
        cout << temp->dato << " ";
        temp = temp->siguiente;
    } while (temp != cabeza);
    cout << endl << endl;
}

void EliminarNodo(Nodo* &cabeza, int valor) {
    if(cabeza == nullptr) {
        cout << "La lista esta vacia\n";
        return;
    }
    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;
    if(temp->dato == valor) {
        if(temp->siguiente == cabeza){
            delete temp;
            cabeza = nullptr;
            cout << "Nodo eliminado\n";
            return;
        }
        Nodo* ultimo  = cabeza;
        while(ultimo->siguiente != cabeza) ultimo = ultimo->siguiente;
        cabeza = temp->siguiente;
        ultimo->siguiente = cabeza;
        delete temp;
        cout << "Nodo eliminado\n";
        return;
    } 

    do {
        anterior = temp;
        temp = temp->siguiente;
        if(temp->dato == valor) {
            anterior->siguiente = temp->siguiente;
            delete temp;
            cout << "Nodo eliminado\n";
            return;
        }
    } while(temp != cabeza);
}

void PushFront(Nodo* &cabeza, int valor) {
    Nodo* nuevo = NuevoNodo(valor);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != cabeza) temp = temp->siguiente;
        temp->siguiente = nuevo;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }
    cout << "Nodo agregado\n";
}

void EliminarNodos(Nodo* &cabeza) {
    if(cabeza == nullptr) {
        cout << "La lista esta vacia\n";
        return;
    }
    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;
    do {
        anterior = temp;
        temp = temp->siguiente;
        delete anterior;
    } while(temp != cabeza);
    cabeza = nullptr;
    cout << "Nodos eliminados\n";
}

void Aplanar(Nodo* &cabeza) {
    if (cabeza == nullptr) return;
    Nodo* temp = cabeza;
    while (temp->siguiente != cabeza) {
        temp = temp->siguiente;
    }
    temp->siguiente = nullptr;
}

void printLinear(Nodo* cabeza) {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << temp->dato << " ";
        temp = temp->siguiente;
    }
    cout << endl << endl;
}

int main() {
    Nodo* cabeza = nullptr;
    PushBack(cabeza, 1);
    PushBack(cabeza, 2);
    PushBack(cabeza, 3);
    PushBack(cabeza, 4);
    PushBack(cabeza, 5);
    cout << "Lista original: ";
    print(cabeza);
    
    EliminarNodo(cabeza, 3);
    cout << "Lista despues de eliminar un nodo: ";
    print(cabeza);
    
    PushFront(cabeza, 0);
    cout << "Lista despues de agregar un nodo al inicio: ";
    print(cabeza);

    cout << "Aplanando la lista circular..." << endl;
    Aplanar(cabeza);
    cout << "Lista despues de aplanar (lineal): ";
    printLinear(cabeza);

    // Liberar la lista lineal
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        Nodo* sig = temp->siguiente;
        delete temp;
        temp = sig;
    }
    cabeza = nullptr;
    cout << "Memoria liberada." << endl;
    
    return 0;
}

