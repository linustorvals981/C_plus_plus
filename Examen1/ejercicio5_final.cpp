#include <iostream>

using namespace std;

struct Nodo {
  float promedio;
  Nodo *siguiente;

  Nodo(float p) : promedio(p), siguiente(nullptr) {}
};

//////////////////////////////////////////////////////////////
// INSERTAR AL FINAL
//////////////////////////////////////////////////////////////

void insertar(Nodo *&head, float promedio) {
  Nodo *nuevo = new Nodo(promedio);

  if (head == nullptr) {
    head = nuevo;
    nuevo->siguiente = nuevo;
    return;
  }

  Nodo *ultimo = head;

  while (ultimo->siguiente != head)
    ultimo = ultimo->siguiente;

  ultimo->siguiente = nuevo;
  nuevo->siguiente = head;
}

//////////////////////////////////////////////////////////////
// MOSTRAR
//////////////////////////////////////////////////////////////

void mostrar(Nodo *head) {
  if (head == nullptr) {
    cout << "Lista vacia\n";
    return;
  }

  Nodo *aux = head;

  do {
    cout << aux->promedio << " ";
    aux = aux->siguiente;

  } while (aux != head);

  cout << endl;
}

//////////////////////////////////////////////////////////////
// PARTICIONAR REUTILIZANDO NODOS
//////////////////////////////////////////////////////////////

Nodo *partition(Nodo *&head) {
  if (head == nullptr)
    return nullptr;

  Nodo *mayores = nullptr;
  Nodo *menores = nullptr;

  Nodo *mayoresTail = nullptr;
  Nodo *menoresTail = nullptr;

  Nodo *actual = head;
  Nodo *inicio = head;

  do {
    Nodo *siguiente = actual->siguiente;

    // Desconectar temporalmente
    actual->siguiente = actual;

    if (actual->promedio >= 8.0f) {
      if (mayores == nullptr) {
        mayores = actual;
        mayoresTail = actual;
      } else {
        actual->siguiente = mayores;
        mayoresTail->siguiente = actual;
        mayoresTail = actual;
      }
    } else {
      if (menores == nullptr) {
        menores = actual;
        menoresTail = actual;
      } else {
        actual->siguiente = menores;
        menoresTail->siguiente = actual;
        menoresTail = actual;
      }
    }

    actual = siguiente;

  } while (actual != inicio);

  head = menores;
  return mayores;
}

//////////////////////////////////////////////////////////////
// LIBERAR MEMORIA
//////////////////////////////////////////////////////////////

void destruirLista(Nodo *&head) {
  if (head == nullptr)
    return;

  Nodo *actual = head->siguiente;

  while (actual != head) {
    Nodo *temp = actual;
    actual = actual->siguiente;
    delete temp;
  }

  delete head;
  head = nullptr;
}

//////////////////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////////////////

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

  cout << "Lista original:\n";
  mostrar(head);

  Nodo *mayores = partition(head);

  cout << "\nPromedios menores a 8.0:\n";
  mostrar(head);

  cout << "\nPromedios mayores o iguales a 8.0:\n";
  mostrar(mayores);

  destruirLista(head);
  destruirLista(mayores);

  return 0;
}