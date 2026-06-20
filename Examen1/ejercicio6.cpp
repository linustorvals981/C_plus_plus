#include <iostream>

using namespace std;

struct Nodo {
  int info;
  Nodo *sig;
  Nodo *ant;
};

Nodo *crearNodo(int val) {
  Nodo *n = new Nodo;
  n->info = val;
  n->sig = nullptr;
  n->ant = nullptr;
  return n;
}

void insertar(Nodo *&frente, Nodo *&final, int val) {
  Nodo *aux = crearNodo(val);
  if (frente == nullptr) {
    frente = aux;
    final = aux;
  } else {
    final->sig = aux;
    aux->ant = final;
    final = aux;
  }
}

void mostrar(Nodo *frente) {
  Nodo *ptr = frente;
  while (ptr != nullptr) {
    cout << ptr->info << " ";
    ptr = ptr->sig;
  }
  cout << endl;
}

void mezclar(Nodo *&frente, Nodo *&final) {
  if (frente == nullptr || frente == final)
    return;

  Nodo *izq = frente;
  Nodo *der = final;

  while (true) {
    if (izq == der || izq->sig == der) {
      if (izq->sig == der) {
        izq->sig = der;
        der->sig = nullptr;
      }
      break;
    }

    Nodo *proxIzq = izq->sig;
    Nodo *prevDer = der->ant;

    izq->sig = der;
    der->sig = proxIzq;
    proxIzq->ant = der;
    prevDer->sig = nullptr;

    izq = proxIzq;
    der = prevDer;
  }

  final = der;
}

int main() {
  Nodo *frente = nullptr;
  Nodo *final = nullptr;

  insertar(frente, final, 1);
  insertar(frente, final, 2);
  insertar(frente, final, 3);
  insertar(frente, final, 4);
  insertar(frente, final, 5);
  insertar(frente, final, 6);

  cout << "Lista original: ";
  mostrar(frente);

  mezclar(frente, final);

  cout << "Lista entrelazada: ";
  mostrar(frente);

  return 0;
}