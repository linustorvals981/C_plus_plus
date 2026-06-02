#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor)
        : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

Nodo* NuevoNodo(int valor) {
    return new Nodo(valor);
}

void PushBack(Nodo*& cabeza, int valor) {
    Nodo* nuevo = NuevoNodo(valor);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
        return;
    }

    Nodo* ultimo = cabeza->anterior;

    ultimo->siguiente = nuevo;
    nuevo->anterior = ultimo;

    nuevo->siguiente = cabeza;
    cabeza->anterior = nuevo;
}

void PushFront(Nodo*& cabeza, int valor) {
    Nodo* nuevo = NuevoNodo(valor);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
        return;
    }

    Nodo* ultimo = cabeza->anterior;

    nuevo->siguiente = cabeza;
    nuevo->anterior = ultimo;

    ultimo->siguiente = nuevo;
    cabeza->anterior = nuevo;

    cabeza = nuevo;
}

void PrintForward(Nodo* cabeza) {
    if (cabeza == nullptr) return;

    Nodo* temp = cabeza;

    do {
        cout << temp->dato << " ";
        temp = temp->siguiente;
    } while (temp != cabeza);

    cout << endl;
}

void PrintBackward(Nodo* cabeza) {
    if (cabeza == nullptr) return;

    Nodo* temp = cabeza->anterior;

    do {
        cout << temp->dato << " ";
        temp = temp->anterior;
    } while (temp != cabeza->anterior);

    cout << endl;
}

void EliminarNodo(Nodo*& cabeza, int valor) {

    if (cabeza == nullptr) {
        cout << "Lista vacia\n";
        return;
    }

    Nodo* actual = cabeza;

    do {

        if (actual->dato == valor) {

            if (actual->siguiente == actual) {
                delete actual;
                cabeza = nullptr;
                return;
            }

            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;

            if (actual == cabeza)
                cabeza = actual->siguiente;

            delete actual;
            return;
        }

        actual = actual->siguiente;

    } while (actual != cabeza);

    cout << "Valor no encontrado\n";
}

void EliminarNodos(Nodo*& cabeza) {

    if (cabeza == nullptr)
        return;

    Nodo* actual = cabeza->siguiente;

    while (actual != cabeza) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    delete cabeza;
    cabeza = nullptr;
}

int main() {

    Nodo* cabeza = nullptr;

    // --- PushBack ---
    cout << "=== PushBack (1, 2, 3, 4, 5) ===\n";
    PushBack(cabeza, 1);
    PushBack(cabeza, 2);
    PushBack(cabeza, 3);
    PushBack(cabeza, 4);
    PushBack(cabeza, 5);
    PrintForward(cabeza);

    // --- PrintBackward ---
    cout << "\n=== PrintBackward ===\n";
    PrintBackward(cabeza);

    // --- PushFront ---
    cout << "\n=== PushFront (0) ===\n";
    PushFront(cabeza, 0);
    PrintForward(cabeza);

    // --- EliminarNodo (intermedio) ---
    cout << "\n=== EliminarNodo (valor=3, nodo intermedio) ===\n";
    EliminarNodo(cabeza, 3);
    PrintForward(cabeza);

    // --- EliminarNodo (cabeza) ---
    cout << "\n=== EliminarNodo (valor=0, cabeza) ===\n";
    EliminarNodo(cabeza, 0);
    PrintForward(cabeza);

    // --- EliminarNodo (ultimo) ---
    cout << "\n=== EliminarNodo (valor=5, ultimo nodo) ===\n";
    EliminarNodo(cabeza, 5);
    PrintForward(cabeza);

    // --- EliminarNodo (valor no existe) ---
    cout << "\n=== EliminarNodo (valor=99, no existe) ===\n";
    EliminarNodo(cabeza, 99);

    // --- Lista con un solo nodo ---
    cout << "\n=== Lista con un solo nodo ===\n";
    Nodo* solo = nullptr;
    PushBack(solo, 42);
    PrintForward(solo);
    PrintBackward(solo);
    EliminarNodo(solo, 42);  // debe quedar en nullptr
    cout << "Despues de eliminar unico nodo: ";
    PrintForward(solo);      // no imprime nada
    cout << "(lista vacia)\n";

    // --- EliminarNodos (limpiar todo) ---
    cout << "\n=== EliminarNodos (limpiar lista completa) ===\n";
    EliminarNodos(cabeza);
    cout << "Lista despues de EliminarNodos: ";
    PrintForward(cabeza);    // no imprime nada
    cout << "(lista vacia)\n";

    // --- EliminarNodos sobre lista ya vacia ---
    cout << "\n=== EliminarNodos sobre lista vacia (no debe crashear) ===\n";
    EliminarNodos(cabeza);
    cout << "OK\n";

    return 0;
}
// int main() {

//     Nodo* cabeza = nullptr;

//     PushBack(cabeza, 1);
//     PushBack(cabeza, 2);
//     PushBack(cabeza, 3);
//     PushBack(cabeza, 4);
//     PushBack(cabeza, 5);

//     cout << "Recorrido hacia adelante:\n";
//     PrintForward(cabeza);

//     cout << "Recorrido hacia atras:\n";
//     PrintBackward(cabeza);

//     PushFront(cabeza, 0);

//     cout << "\nDespues de PushFront:\n";
//     PrintForward(cabeza);

//     EliminarNodo(cabeza, 3);

//     cout << "\nDespues de eliminar 3:\n";
//     PrintForward(cabeza);

//     EliminarNodos(cabeza);

//     return 0;
// }
