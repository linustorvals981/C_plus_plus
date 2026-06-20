#include <iostream>

using namespace std;

struct Nodo {
  int info;
  Nodo *sig;
  Nodo *ant;

  Nodo(int val) : info(val), sig(nullptr), ant(nullptr) {}
};

class Lista {
private:
  Nodo *frente;
  Nodo *final;

public:
  Lista() : frente(nullptr), final(nullptr) {}

  // Destructor: evita memory leaks
  ~Lista() { liberar(); }

  void insertar(int valor) {
    Nodo *nuevo = new Nodo(valor);

    if (!frente) {
      frente = final = nuevo;
      return;
    }

    final->sig = nuevo;
    nuevo->ant = final;
    final = nuevo;
  }

  void mostrarAdelante() const {
    Nodo *p = frente;

    while (p) {
      cout << p->info << " ";
      p = p->sig;
    }

    cout << endl;
  }

  void mostrarAtras() const {
    Nodo *p = final;

    while (p) {
      cout << p->info << " ";
      p = p->ant;
    }

    cout << endl;
  }

  void mezclar() {
    if (!frente || frente == final)
      return;

    Nodo *izq = frente;
    Nodo *der = final;

    while (izq != der && izq->sig != der) {

      Nodo *proxIzq = izq->sig;
      Nodo *prevDer = der->ant;

      //----------------------------------
      // Insertar der después de izq
      //----------------------------------

      izq->sig = der;
      der->ant = izq;

      der->sig = proxIzq;
      proxIzq->ant = der;

      //----------------------------------
      // Cortar la cola anterior
      //----------------------------------

      prevDer->sig = nullptr;

      //----------------------------------
      // Avanzar
      //----------------------------------

      izq = proxIzq;
      der = prevDer;
    }

    //----------------------------------
    // Reconstruir TODOS los punteros ant
    //----------------------------------

    Nodo *anterior = nullptr;
    Nodo *actual = frente;

    while (actual) {
      actual->ant = anterior;
      anterior = actual;

      if (actual->sig == nullptr)
        final = actual;

      actual = actual->sig;
    }
  }

  void liberar() {

    Nodo *actual = frente;

    while (actual) {

      Nodo *siguiente = actual->sig;

      delete actual;

      actual = siguiente;
    }

    frente = nullptr;
    final = nullptr;
  }
};

int main() {

  Lista lista;

  lista.insertar(1);
  lista.insertar(2);
  lista.insertar(3);
  lista.insertar(4);
  lista.insertar(5);
  lista.insertar(6);

  cout << "Lista original:" << endl;
  lista.mostrarAdelante();

  lista.mezclar();

  cout << "\nLista mezclada:" << endl;
  lista.mostrarAdelante();

  cout << "\nRecorrido inverso:" << endl;
  lista.mostrarAtras();

  return 0;
}