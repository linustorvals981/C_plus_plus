#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
};

void inserta(Nodo*& head, int dato) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = nullptr;
    nuevo->anterior = nullptr;

    if (head == nullptr) {
        head = nuevo;
        return;
    }

    Nodo* aux = head;
    while (aux->siguiente != nullptr)
        aux = aux->siguiente;

    aux->siguiente = nuevo;
    nuevo->anterior = aux;
}

Nodo* obtenerFin(Nodo* head) {
    if (head == nullptr)
        return nullptr;

    while (head->siguiente != nullptr)
        head = head->siguiente;

    return head;
}

//Ejemplo [10<->20<->30<->40<->50] → [10<->50<->20<->40<->30]
void fold(Nodo* &inicio, Nodo* &fin){
    if (inicio == nullptr || inicio->siguiente == nullptr){
        return;
    }

    Nodo* head = inicio;
    Nodo* tail = fin;
    
    while (inicio != fin) {
        Nodo* temp = inicio->siguiente;
        Nodo* temp2 = fin->anterior;
        inicio->siguiente = fin;
        fin->anterior = inicio;
        fin->siguiente = temp;
        inicio = temp;
        fin = temp2;
    }

    head->anterior = nullptr;
    tail->siguiente = nullptr;
}

void mostrar(Nodo* head) {
    if (head == nullptr) {
        cout << "[]" << endl;
        return;
    }

    Nodo* aux = head;
    while (aux != nullptr) {
        cout << "[ " << aux->dato << " ]";
        if (aux->siguiente != nullptr)
            cout << " <-> ";
        aux = aux->siguiente;
    }
    cout << endl;
}

int main() {
    Nodo* head = nullptr;

    inserta(head, 10);
    inserta(head, 20);
    inserta(head, 30);
    inserta(head, 40);
    inserta(head, 50);

    cout << "Lista original:\n";
    mostrar(head, obtenerFin(head));

    fold(head, obtenerFin(head));

    cout << "\nLista despues de fold:\n";
    mostrar(head);

    return 0;
}
