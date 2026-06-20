#include <iostream>

using namespace std;

struct Nodo {
  float promedio;
  Nodo *siguiente;
};

void insertar(Nodo *&head, float promedio) {
  Nodo *nuevo = new Nodo;
  nuevo->promedio = promedio;

  if (head == nullptr) {
    head = nuevo;
    nuevo->siguiente = nuevo;
    return;
  }

  Nodo *aux = head;
  while (aux->siguiente != head)
    aux = aux->siguiente;

  nuevo->siguiente = head;
  aux->siguiente = nuevo;
}

void mostrar(Nodo *head) {
  if (head == nullptr) {
    cout << "Lista vacia" << endl;
    return;
  }

  Nodo *aux = head;

  do {
    cout << aux->promedio << " ";
    aux = aux->siguiente;
  } while (aux != head);

  cout << endl;
}

Nodo *partition(Nodo *&head) {

  if (head == nullptr)
    return nullptr;

  Nodo *mayores = nullptr;
  Nodo *menores = nullptr;

  Nodo *actual = head;

  do {
    if (actual->promedio >= 8.0)
      insertar(mayores, actual->promedio);
    else
      insertar(menores, actual->promedio);

    actual = actual->siguiente;

  } while (actual != head);

  head = menores;
  return mayores;
}

int main() {

  Nodo *head = nullptr;

  insertar(head, 10.0);
  insertar(head, 3.6);
  insertar(head, 8.5);
  insertar(head, 6.5);
  insertar(head, 4.5);
  insertar(head, 7.5);
  insertar(head, 6.5);
  insertar(head, 4.5);
  insertar(head, 7.5);
  insertar(head, 9.5);
  insertar(head, 9.6);
  insertar(head, 9.5);
  insertar(head, 1.5);

  cout << "Lista original:" << endl;
  mostrar(head);

  Nodo *head2 = partition(head);

  cout << "\nPromedios menores a 8.0:" << endl;
  mostrar(head);

  cout << "\nPromedios mayores o iguales a 8.0:" << endl;
  mostrar(head2);

  return 0;
}